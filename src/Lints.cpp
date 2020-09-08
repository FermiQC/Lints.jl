#include "jlcxx/jlcxx.hpp"
#include "jlcxx/tuple.hpp"
#include "libint2.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <math.h>

//
void libint2_init()
{
    libint2::initialize();
}

void libint2_finalize()
{
    libint2::finalize();
}

int ncart(int am)
{
    return ((am >= 0) ? ((((am) + 2) * ((am) + 1)) >> 1) : 0);
}


std::vector<libint2::Atom> get_atoms(const std::string& inp)
{
    std::ifstream input_file(inp);
    std::vector<libint2::Atom> atoms = libint2::read_dotxyz(input_file);
    return atoms;
}

libint2::Engine make_engine(libint2::Operator op, int max_nprim, int max_l)
{
    return libint2::Engine(op, max_nprim, max_l);
}

struct Atom
{
    Atom(int Z, double x, double y, double z) {
        _atom.atomic_number = Z;
        _atom.x = x;
        _atom.y = y;
        _atom.z = z;
    }
    Atom(libint2::Atom& atom) : _atom(atom) {}

    int Z() const { return _atom.atomic_number; }

    auto get_pos() -> jlcxx::Array<double> { 
        jlcxx::Array<double> pos;
        pos.push_back(_atom.x);
        pos.push_back(_atom.y);
        pos.push_back(_atom.z);
        return pos;
    }

    void set_pos(double x, double y, double z) {
        _atom.x = x;
        _atom.y = y;
        _atom.z = z;
    }

private:
    libint2::Atom _atom;
};

struct Molecule
{
    Molecule(const jlcxx::ArrayRef<int64_t>& zs, const jlcxx::ArrayRef<double>& coords) {
        for (int i=0, j=0; i < zs.size(); i++, j += 3) {
            _atoms.push_back({.atomic_number = (int)zs[i], .x = coords[j], .y = coords[j+1], .z = coords[j+2]});
        }
    } 
    Molecule(const std::string& inp) {
        _atoms = get_atoms(inp);
    }
    auto push_back(int Z, double x, double y, double z) {
        libint2::Atom atom;//(Z,x,y,z);
        atom.atomic_number = Z;
        atom.x = x;
        atom.y = y;
        atom.z = z;
        _atoms.push_back(atom);
        _Atoms.push_back(Atom(atom));
    }
    auto get_Atom(int i) -> Atom {
        return Atom(_atoms[i]);
    }
    auto get_Atoms() -> jlcxx::Array<Atom> {
        jlcxx::Array<Atom> Atoms;
        for(int i=0; i < _atoms.size(); i++) {
            Atoms.push_back(get_Atom(i));
        }
        return Atoms;
    }
    auto get_size() -> int {
        return _atoms.size();
    }

    const std::vector<libint2::Atom>& atoms() const {
        return _atoms;
    }

private:
    jlcxx::Array<Atom> _Atoms;
    std::vector<libint2::Atom> _atoms;
};

struct BasisSet
{
    BasisSet(const std::string& bname, Molecule mol) : basis(bname, mol.atoms(), true), _mol(std::move(mol)) { }

    void print_out() {
        std::copy(begin(basis),end(basis),
                  std::ostream_iterator<libint2::Shell>(std::cout, "\n"));
    }
    auto nshell() const {
        return basis.size();
    }
    auto nao() {
        int d1 = 0;
        for(int n1=0; n1<nshell(); n1++) {
            d1 += basis[n1].size();
        }
        return d1;
    }
    long max_nprim() {
        return basis.max_nprim();
    }
    long max_l() {
        return basis.max_l();
    }
    Molecule get_mol() {
        return _mol;
    }
    void set_pure(bool tf) {
        this->basis.set_pure(tf);
    }

    libint2::BasisSet basis;

private:
    Molecule _mol;
};

//one electron integral engine parent struct
struct OEIEngine
{
    OEIEngine() = delete;
    OEIEngine(int max_l, libint2::Engine&& engine) : _engine(std::move(engine)), _bufsz(0), _maxl(ncart(max_l)) {}

    void init(const BasisSet& obs1, const BasisSet& obs2) {
        obs1_shell2bf = obs1.basis.shell2bf();
        obs2_shell2bf = obs2.basis.shell2bf();
    }
    
    virtual void compute(jlcxx::ArrayRef<double> buf, int s1, int s2, const BasisSet& obs1, const BasisSet& obs2) {
        const auto& buf_vec = _engine.results();
        _engine.compute(obs1.basis[s1],obs2.basis[s2]);
        auto n1 = obs1.basis[s1].size();
        auto n2 = obs2.basis[s2].size();
        auto ints_shellset = buf_vec[0];
        double *data = (double*)jl_array_data(buf.wrapped());
        if (ints_shellset) {
            memcpy(data,ints_shellset,n2*n1*sizeof(double));
        }
        else {
            memset(data,0,n1*n2*sizeof(double));
        }
        _bufsz = n1*n2;
    }
    
    void chunk(jlcxx::ArrayRef<int64_t> dims, int s1, int s2, const BasisSet& obs1, const BasisSet& obs2) {
        dims[0] = obs1.basis[s1].size();
        dims[1] = obs2.basis[s2].size();
    }
    
    void startpoint(jlcxx::ArrayRef<int64_t> coords, int s1, int s2, const BasisSet& obs1, const BasisSet& obs2) {
        coords[0] = this->obs1_shell2bf[s1];
        coords[1] = this->obs2_shell2bf[s2];
    }
    
    void normalize() {
        _engine.set(libint2::CartesianShellNormalization::uniform);
    }
    
    auto maxl() {
        return this->_maxl;
    }
    
    auto bufsz() {
        return this->_bufsz;
    }

protected:
    libint2::Engine _engine;
    int _bufsz;
    int _maxl;
    std::vector<long unsigned int> obs1_shell2bf;
    std::vector<long unsigned int> obs2_shell2bf;
};

struct OverlapEngine : OEIEngine
{
    OverlapEngine(int max_nprim, int max_l) : OEIEngine(max_l, make_engine(libint2::Operator::overlap,max_nprim,max_l)) {}
};

struct DipoleEngine : OEIEngine
{
    DipoleEngine(int max_nprim, int max_l, double x=0.0, double y=0.0, double z=0.0) : OEIEngine(max_l, make_engine(libint2::Operator::emultipole1,max_nprim,max_l)) {
        std::array<double, 3> ctr = {x, y, z};
        _engine.set_params(ctr);
    }

    double* _mux;
    double* _muy;
    double* _muz;
    
    void compute(int s1, int s2, const BasisSet& obs1, const BasisSet& obs2) {
        const auto& buf_vec = _engine.results();
        _engine.compute(obs1.basis[s1],obs2.basis[s2]);

        auto n1 = obs1.basis[s1].size();
        auto n2 = obs2.basis[s2].size();
        auto s_shellset = buf_vec[0];
        auto mux_shellset = buf_vec[1];
        auto muy_shellset = buf_vec[2];
        auto muz_shellset = buf_vec[3];
        if (s_shellset == nullptr) {
            memset(this->_mux,0,n1*n2*sizeof(double));
            memset(this->_muy,0,n1*n2*sizeof(double));
            memset(this->_muz,0,n1*n2*sizeof(double));
        }
        else {
            memcpy(this->_mux,mux_shellset,n1*n2*sizeof(double));
            memcpy(this->_muy,muy_shellset,n1*n2*sizeof(double));
            memcpy(this->_muz,muz_shellset,n1*n2*sizeof(double));
        }
        this->_bufsz = n1*n2;
    }
    auto recenter(double x=0.0, double y=0.0, double z=0.0) {
        std::array<double, 3> ctr = {x, y, z};
        _engine.set_params(ctr);
    }
    auto mux() {
        return this->_mux;
    }
    auto muy() {
        return this->_muy;
    }
    auto muz() {
        return this->_muz;
    }
};

struct KineticEngine : OEIEngine
{
    KineticEngine(int max_nprim, int max_l) : OEIEngine(max_l, make_engine(libint2::Operator::kinetic,max_nprim,max_l)) {}
};

struct NuclearEngine : OEIEngine
{
    NuclearEngine(int max_nprim, int max_l, Molecule mol) : OEIEngine(max_l, make_engine(libint2::Operator::nuclear, max_nprim, max_l)) {
        _engine.set_params(libint2::make_point_charges(mol.atoms()));
    }
};

struct ERI4Engine
{
    ERI4Engine(int max_nprim, int max_l) : _engine(make_engine(libint2::Operator::coulomb, max_nprim, max_l)), _bufsz(0), _maxl(ncart(max_l)) { }

    void init(const BasisSet& obs) {
        shell2bf = obs.basis.shell2bf();
    }

    void compute(jlcxx::ArrayRef<double> buf, int s1, int s2, int s3, int s4, BasisSet& obs) {
        const auto& buf_vec = _engine.results();
        _engine.compute(obs.basis[s1],obs.basis[s2],obs.basis[s3],obs.basis[s4]);

        auto n1 = obs.basis[s1].size();
        auto n2 = obs.basis[s2].size();
        auto n3 = obs.basis[s3].size();
        auto n4 = obs.basis[s4].size();
        auto ints_shellset = buf_vec[0];
        double *data = (double*)jl_array_data(buf.wrapped());
        if (ints_shellset) {
            memcpy(data,ints_shellset,n1*n2*n3*n4*sizeof(double));
        }
        else {
            memset(data,0,n1*n2*n3*n4*sizeof(double));
        }
        _bufsz = n1*n2*n3*n4;

    }

    void normalize() {
        _engine.set(libint2::CartesianShellNormalization::uniform);
    }

    void chunk(jlcxx::ArrayRef<int64_t> dims, int s1, int s2, int s3, int s4, const BasisSet& obs) {
        dims[0] = obs.basis[s1].size();
        dims[1] = obs.basis[s2].size();
        dims[2] = obs.basis[s3].size();
        dims[3] = obs.basis[s4].size();
    }

    void startpoint(jlcxx::ArrayRef<int64_t> coords, int s1, int s2, int s3, int s4, const BasisSet& obs) {
        coords[0] = shell2bf[s1];
        coords[1] = shell2bf[s2];
        coords[2] = shell2bf[s3];
        coords[3] = shell2bf[s4];
    }

    auto bufsz() -> int {
        return _bufsz;
    }

    auto maxl() -> int {
        return _maxl;
    }

private:
    libint2::Engine _engine;
    int _bufsz;
    int _maxl;
    std::vector<long unsigned int> shell2bf;
};

struct ERI3Engine
{
    ERI3Engine(int max_nprim, int max_l) : _engine(make_engine(libint2::Operator::coulomb, max_nprim, max_l)), _bufsz(0), _maxl(ncart(max_l)) { 
        _engine.set(libint2::BraKet::xs_xx);
    }

    void init(const BasisSet& obs, const BasisSet& dfobs) {
        _obs_shell2bf = obs.basis.shell2bf();
        _dfobs_shell2bf = dfobs.basis.shell2bf();
    }

    void compute(jlcxx::ArrayRef<double> buf, int s3, int s2, int s1, const BasisSet& obs, const BasisSet& dfobs) {
        const auto& buf_vec = _engine.results();
        _engine.compute(dfobs.basis[s3],obs.basis[s2],obs.basis[s1]);
        
        auto n1 = obs.basis[s1].size();
        auto n2 = obs.basis[s2].size();
        auto n3 = dfobs.basis[s3].size();
        auto ints_shellset = buf_vec[0];
        double *data = (double*)jl_array_data(buf.wrapped());
        if (ints_shellset) {
            memcpy(data,ints_shellset,n1*n2*n3*sizeof(double));
        }
        else {
            memset(data,0,n1*n2*n3*sizeof(double));
        }
        _bufsz = n1*n2*n3;
    }

    void normalize() {
        _engine.set(libint2::CartesianShellNormalization::uniform);
    }

    void chunk(jlcxx::ArrayRef<int64_t> dims, int s3, int s2, int s1, const BasisSet& obs, const BasisSet& dfobs) {
        dims[0] = dfobs.basis[s3].size();
        dims[1] = obs.basis[s2].size();
        dims[2] = obs.basis[s1].size();
    }

    void startpoint(jlcxx::ArrayRef<int64_t> coords, int s3, int s2, int s1, const BasisSet& obs, const BasisSet& dfobs) {
        coords[0] = _dfobs_shell2bf[s3];
        coords[1] = _obs_shell2bf[s2];
        coords[2] = _obs_shell2bf[s1];
    }


    auto maxl() const {
        return _maxl;
    }

    auto bufsz() const {
        return _bufsz;
    }

private:
    libint2::Engine _engine;
    int _bufsz;
    int _maxl;
    double* _data;
    std::vector<long unsigned int> _obs_shell2bf;
    std::vector<long unsigned int> _dfobs_shell2bf;
};

//not ~exactly~ a one electron integral, but functions the same
struct ERI2Engine : OEIEngine 
{
    ERI2Engine(int max_nprim, int max_l) : OEIEngine(max_l, make_engine(libint2::Operator::coulomb, max_nprim, max_l)) {
        _engine.set(libint2::BraKet::xs_xs);
    }
};

JLCXX_MODULE Libint2(jlcxx::Module& mod)
{
    mod.method("libint2_init",&libint2_init);
    mod.method("libint2_finalize",&libint2_finalize);
    mod.add_type<Atom>("Atom")
        .constructor<int,double,double,double>()
        .method("Z",&Atom::Z)
        .method("get_pos",&Atom::get_pos)
        .method("set_pos",&Atom::set_pos);

    mod.add_type<Molecule>("Molecule")
        .constructor<std::string&>()
        .constructor<jlcxx::ArrayRef<int64_t>,jlcxx::ArrayRef<double>>()
        .method("get_Atom",&Molecule::get_Atom)
        .method("get_Atoms",&Molecule::get_Atoms)
        .method("get_size",&Molecule::get_size)
        .method("push_back",&Molecule::push_back);

    mod.add_type<BasisSet>("BasisSet")
        .constructor<std::string&, std::string&>()
        .constructor<std::string&, Molecule>()
        .method("get_mol",&BasisSet::get_mol)
        .method("nao",&BasisSet::nao)
        .method("nshell",&BasisSet::nshell)
        .method("print_out",&BasisSet::print_out)
        .method("max_nprim",&BasisSet::max_nprim)
        .method("set_pure",&BasisSet::set_pure)
        .method("max_l",&BasisSet::max_l);
        
    mod.add_type<OverlapEngine>("OverlapEngine")
        .constructor<int, int>()
        .method("init",&OverlapEngine::init)
        .method("normalize",&OverlapEngine::normalize)
        .method("maxl",&OverlapEngine::maxl)
        .method("bufsz",&OverlapEngine::bufsz)
        .method("compute",&OverlapEngine::compute)
        .method("chunk",&OverlapEngine::chunk)
        .method("startpoint",&OverlapEngine::startpoint);

    mod.add_type<DipoleEngine>("DipoleEngine")
        .constructor<int, int, double, double, double>()
        .method("compute",&DipoleEngine::compute)
        .method("chunk",&DipoleEngine::chunk)
        .method("mux",&DipoleEngine::mux)
        .method("muy",&DipoleEngine::muy)
        .method("muz",&DipoleEngine::muz)
        .method("startpoint",&DipoleEngine::startpoint);

    mod.add_type<NuclearEngine>("NuclearEngine")
        .constructor<int,int,Molecule>()
        .method("init",&NuclearEngine::init)
        .method("normalize",&NuclearEngine::normalize)
        .method("maxl",&NuclearEngine::maxl)
        .method("bufsz",&NuclearEngine::bufsz)
        .method("compute",&NuclearEngine::compute)
        .method("startpoint",&NuclearEngine::startpoint)
        .method("chunk",&NuclearEngine::chunk);

    mod.add_type<KineticEngine>("KineticEngine")
        .constructor<int,int>()
        .method("init",&KineticEngine::init)
        .method("normalize",&KineticEngine::normalize)
        .method("maxl",&KineticEngine::maxl)
        .method("bufsz",&KineticEngine::bufsz)
        .method("compute",&KineticEngine::compute)
        .method("startpoint",&KineticEngine::startpoint)
        .method("chunk",&KineticEngine::chunk);

    mod.add_type<ERI4Engine>("ERI4Engine")
        .constructor<int,int>()
        .method("init",&ERI4Engine::init)
        .method("normalize",&ERI4Engine::normalize)
        .method("maxl",&ERI4Engine::maxl)
        .method("bufsz",&ERI4Engine::bufsz)
        .method("compute",&ERI4Engine::compute)
        .method("startpoint",&ERI4Engine::startpoint)
        .method("chunk",&ERI4Engine::chunk);

    mod.add_type<ERI3Engine>("ERI3Engine")
        .constructor<int,int>()
        .method("init",&ERI3Engine::init)
        .method("normalize",&ERI3Engine::normalize)
        .method("compute",&ERI3Engine::compute)
        .method("bufsz",&ERI3Engine::bufsz)
        .method("chunk",&ERI3Engine::chunk)
        .method("maxl",&ERI3Engine::maxl)
        .method("startpoint",&ERI3Engine::startpoint);

    mod.add_type<ERI2Engine>("ERI2Engine")
        .constructor<int,int>()
        .method("init",&ERI2Engine::init)
        .method("normalize",&ERI2Engine::normalize)
        .method("compute",&ERI2Engine::compute)
        .method("bufsz",&ERI2Engine::bufsz)
        .method("chunk",&ERI2Engine::chunk)
        .method("maxl",&ERI2Engine::maxl)
        .method("startpoint",&ERI2Engine::startpoint);
}
