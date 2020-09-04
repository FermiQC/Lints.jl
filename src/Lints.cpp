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

//recursive function to determine number of cartesian gaussians for a given AM. 
//since this is always >= number of sph. harmonics for a given AM, we use this
//for building buffers.
int nharms(int n)
{
    switch(n) {
        case 0: // s 
            return 1;
            break;
        case 1: // p 
            return 3;
            break;
        case 2: // d
            return 6;
            break;
        default: // f+
            return n*3 + nharms(n-3);
    }
}


std::vector<libint2::Atom> get_atoms(std::string& inp)
{
    std::ifstream input_file(inp);
    std::vector<libint2::Atom> atoms = libint2::read_dotxyz(input_file);
    return atoms;
}

libint2::Engine make_engine(libint2::Operator op, int max_nprim, int max_l)
{
    libint2::Engine engine(op,max_nprim,max_l);
    return engine;
}

struct Atom
{
    Atom(int Z, double x, double y, double z) {
        libint2::Atom atom;
        atom.atomic_number = Z;
        atom.x = x;
        atom.y = y;
        atom.z = z;
        this->atom = atom;
    }
    Atom(libint2::Atom& atom) {
        this->atom = atom;
    }
    libint2::Atom atom;
    int Z() { return this->atom.atomic_number; }
    auto get_pos() { 
        jlcxx::Array<double> pos;
        pos.push_back(this->atom.x);
        pos.push_back(this->atom.y);
        pos.push_back(this->atom.z);
        return pos;
    }
    auto set_pos(double x, double y, double z) {
        this->atom.x = x;
        this->atom.y = y;
        this->atom.z = z;
    }
};

struct Molecule
{
    Molecule(jlcxx::ArrayRef<int64_t> zs, jlcxx::ArrayRef<double> coords) {
        std::vector<libint2::Atom> _atoms;
        this->len = zs.size();
        double x, y, z;
        for (int i=0, j=0; i < this->len; i++, j += 3) {
            libint2::Atom a;
            a.atomic_number = zs[i];
            a.x = coords[j];
            a.y = coords[j+1];
            a.z = coords[j+2];
            _atoms.push_back(a);
        }
        this->atoms = _atoms;
    } 
    Molecule(std::string& inp) {
        this->atoms = get_atoms(inp);
        this->len = this->atoms.size();
    }
    auto push_back(int Z, double x, double y, double z) {
        libint2::Atom atom;//(Z,x,y,z);
        atom.atomic_number = Z;
        atom.x = x;
        atom.y = y;
        atom.z = z;
        this->atoms.push_back(atom);
        this->Atoms.push_back(Atom(atom));
        this->len++;
    }
    auto get_Atom(int i) {
        return Atom(this->atoms[i]);
    }
    auto get_Atoms() {
        jlcxx::Array<Atom> Atoms;
        for(int i=0; i < this->atoms.size(); i++) {
            Atoms.push_back(this->get_Atom(i));
        }
        return Atoms;
    }
    auto get_size() {
        return this->len;
    }
    int len;
    jlcxx::Array<Atom> Atoms;
    std::vector<libint2::Atom> atoms;
};

struct BasisSet
{
    libint2::BasisSet basis;
    Molecule mol;
    //BasisSet(std::string bname, std::vector<libint2::Atom> atoms) {
    //    libint2::BasisSet bas(bname, atoms, true);
    //    this->basis = bas;
    //    this->mol = nullptr;
    //}
    BasisSet(std::string bname, Molecule mol) : mol(mol) {
        libint2::BasisSet bas(bname,mol.atoms, true);
        this->basis = bas;
    }
    auto print_out() {
        std::copy(begin(this->basis),end(this->basis),
                  std::ostream_iterator<libint2::Shell>(std::cout, "\n"));
    }
    auto nshell() {
        return this->basis.size();
    }
    auto nao() {
        int d1 = 0;
        for(int n1=0; n1<this->basis.size(); n1++) {
            d1 += this->basis[n1].size();
        }
        return d1;
    }
    long max_nprim() {
        return this->basis.max_nprim();
    }
    long max_l() {
        return this->basis.max_l();
    }
    Molecule get_mol() {
        return this->mol;
    }
    void set_pure(bool tf) {
        this->basis.set_pure(tf);
    }
};

//one electron integral engine parent struct
struct OEIEngine
{
    libint2::Engine engine;
    int _bufsz;
    int _maxl;
    std::vector<long unsigned int> obs1_shell2bf;
    std::vector<long unsigned int> obs2_shell2bf;
    void init(BasisSet& obs1, BasisSet& obs2) {
        this->obs1_shell2bf = obs1.basis.shell2bf();
        this->obs2_shell2bf = obs2.basis.shell2bf();
    }
    virtual void compute(jlcxx::ArrayRef<double> buf, int s1, int s2, BasisSet& obs1, BasisSet& obs2) {
        const auto& buf_vec = this->engine.results();
        this->engine.compute(obs1.basis[s1],obs2.basis[s2]);
        auto n1 = obs1.basis[s1].size();
        auto n2 = obs2.basis[s2].size();
        auto ints_shellset = buf_vec[0];
        double *data = (double*)jl_array_data(buf.wrapped());
        if (ints_shellset == nullptr) {
            double z = 0.0;
            memset(data,z,n1*n2*sizeof(double));
        }
        else {
            memcpy(data,ints_shellset,n2*n1*sizeof(double));
        }
        this->_bufsz = n1*n2;
    }
    void chunk(jlcxx::ArrayRef<int64_t> dims, int s1, int s2, BasisSet& obs1, BasisSet& obs2) {
        dims[0] = obs1.basis[s1].size();
        dims[1] = obs2.basis[s2].size();
    }
    void startpoint(jlcxx::ArrayRef<int64_t> coords, int s1, int s2, BasisSet& obs1, BasisSet& obs2) {
        coords[0] = this->obs1_shell2bf[s1];
        coords[1] = this->obs2_shell2bf[s2];
    }
    void normalize() {
        this->engine.set(libint2::CartesianShellNormalization::uniform);
    }
    auto maxl() {
        return this->_maxl;
    }
    auto bufsz() {
        return this->_bufsz;
    }
};
struct OverlapEngine : OEIEngine
{
    OverlapEngine(int max_nprim, int max_l) {
        this->engine = make_engine(libint2::Operator::overlap,max_nprim,max_l);
        int maxl = nharms(max_l);
        this->_maxl = maxl;
    }
};

struct DipoleEngine : OEIEngine
{
    DipoleEngine(int max_nprim, int max_l, double x=0.0, double y=0.0, double z=0.0) {
        this->engine = make_engine(libint2::Operator::emultipole1,max_nprim,max_l);
        std::array<double, 3> ctr = {x, y, z};
        this->engine.set_params(ctr);
        int maxl = nharms(max_l);
        this->_maxl = maxl;
    }
    double* _mux;
    double* _muy;
    double* _muz;
    int _bufsz;

    void compute(int s1, int s2, BasisSet& obs1, BasisSet& obs2) {
        const auto& buf_vec = this->engine.results();
        this->engine.compute(obs1.basis[s1],obs2.basis[s2]);
        auto n1 = obs1.basis[s1].size();
        auto n2 = obs2.basis[s2].size();
        auto s_shellset = buf_vec[0];
        auto mux_shellset = buf_vec[1];
        auto muy_shellset = buf_vec[2];
        auto muz_shellset = buf_vec[3];
        if (s_shellset == nullptr) {
            double z = 0.0;
            memset(this->_mux,z,n1*n2*sizeof(double));
            memset(this->_muy,z,n1*n2*sizeof(double));
            memset(this->_muz,z,n1*n2*sizeof(double));
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
        this->engine.set_params(ctr);
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
    KineticEngine(int max_nprim, int max_l) {
        this->engine = make_engine(libint2::Operator::kinetic,max_nprim,max_l);
        this->_maxl = nharms(max_l);
    }
};

struct NuclearEngine : OEIEngine
{
    NuclearEngine(int max_nprim, int max_l, Molecule mol) {
        libint2::Engine engine(libint2::Operator::nuclear, max_nprim, max_l);
        engine.set_params(libint2::make_point_charges(mol.atoms));
        this->engine = engine;
        this->_maxl = nharms(max_l);
    }
};

struct ERI4Engine
{
    libint2::Engine engine;
    int _bufsz;
    int _maxl;
    std::vector<long unsigned int> shell2bf;

    ERI4Engine(int max_nprim, int max_l) {
        this->engine = make_engine(libint2::Operator::coulomb,
                                    max_nprim,
                                    max_l);
        this->_maxl = nharms(max_l);
    }

    void init(BasisSet& obs) {
        this->shell2bf = obs.basis.shell2bf();
    }

    void compute(jlcxx::ArrayRef<double> buf, int s1, int s2, int s3, int s4, BasisSet& obs) {
        const auto& buf_vec = this->engine.results();
        this->engine.compute(obs.basis[s1],obs.basis[s2],obs.basis[s3],obs.basis[s4]);
        auto n1 = obs.basis[s1].size();
        auto n2 = obs.basis[s2].size();
        auto n3 = obs.basis[s3].size();
        auto n4 = obs.basis[s4].size();
        auto ints_shellset = buf_vec[0];
        double *data = (double*)jl_array_data(buf.wrapped());
        if (ints_shellset == nullptr) {
            double z = 0.0;
            memset(data,z,n1*n2*n3*n4*sizeof(double));
        }
        else {
            memcpy(data,ints_shellset,n1*n2*n3*n4*sizeof(double));
        }
        this->_bufsz = n1*n2*n3*n4;

    }
    void normalize() {
        this->engine.set(libint2::CartesianShellNormalization::uniform);
    }

    auto chunk(jlcxx::ArrayRef<int64_t> dims, int s1, int s2, int s3, int s4, BasisSet& obs) {
        dims[0] = obs.basis[s1].size();
        dims[1] = obs.basis[s2].size();
        dims[2] = obs.basis[s3].size();
        dims[3] = obs.basis[s4].size();
    }
    auto startpoint(jlcxx::ArrayRef<int64_t> coords, int s1, int s2, int s3, int s4, BasisSet& obs) {
        coords[0] = this->shell2bf[s1];
        coords[1] = this->shell2bf[s2];
        coords[2] = this->shell2bf[s3];
        coords[3] = this->shell2bf[s4];
    }

    auto bufsz() {
        return this->_bufsz;
    }

    auto maxl() {
        return this->_maxl;
    }
};

struct ERI3Engine
{
    int _maxl;
    double* _data;
    std::vector<long unsigned int> obs_shell2bf;
    std::vector<long unsigned int> dfobs_shell2bf;
    int _bufsz;
    libint2::Engine engine;

    ERI3Engine(int max_nprim, int max_l) {
        this->engine = make_engine(libint2::Operator::coulomb,
                                    max_nprim,
                                    max_l);
        this->engine.set(libint2::BraKet::xs_xx);
        this->_maxl = nharms(max_l);
    }

    void init(BasisSet& obs, BasisSet& dfobs) {
        this->obs_shell2bf = obs.basis.shell2bf();
        this->dfobs_shell2bf = dfobs.basis.shell2bf();
    }

    auto compute(jlcxx::ArrayRef<double> buf, int s3, int s2, int s1, BasisSet& obs, BasisSet& dfobs) {
        const auto& buf_vec = this->engine.results();
        this->engine.compute(dfobs.basis[s3],obs.basis[s2],obs.basis[s1]);
        auto n1 = obs.basis[s1].size();
        auto n2 = obs.basis[s2].size();
        auto n3 = dfobs.basis[s3].size();
        auto ints_shellset = buf_vec[0];
        double *data = (double*)jl_array_data(buf.wrapped());
        if (ints_shellset == nullptr) {
            double z = 0.0;
            memset(data,z,n1*n2*n3*sizeof(double));
        }
        else {
            memcpy(data,ints_shellset,n1*n2*n3*sizeof(double));
        }
        this->_bufsz = n1*n2*n3;
    }

    void normalize() {
        this->engine.set(libint2::CartesianShellNormalization::uniform);
    }

    auto chunk(jlcxx::ArrayRef<int64_t> dims, int s3, int s2, int s1, BasisSet& obs, BasisSet& dfobs) {
        dims[0] = dfobs.basis[s3].size();
        dims[1] = obs.basis[s2].size();
        dims[2] = obs.basis[s1].size();
    }

    auto startpoint(jlcxx::ArrayRef<int64_t> coords, int s3, int s2, int s1, BasisSet& obs, BasisSet& dfobs) {
        coords[0] = this->dfobs_shell2bf[s3];
        coords[1] = this->obs_shell2bf[s2];
        coords[2] = this->obs_shell2bf[s1];
    }


    auto maxl() {
        return this->_maxl;
    }

    auto bufsz() {
        return this->_bufsz;
    }

};

//not ~exactly~ a one electron integral, but functions the same
struct ERI2Engine : OEIEngine 
{
    ERI2Engine(int max_nprim, int max_l) {
        this->engine = make_engine(libint2::Operator::coulomb,
                                    max_nprim,
                                    max_l);
        this->engine.set(libint2::BraKet::xs_xs);
        this->_maxl = nharms(max_l);
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
