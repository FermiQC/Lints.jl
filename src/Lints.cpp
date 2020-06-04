#include "jlcxx/jlcxx.hpp"
#include "libint2.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

void libint2_init()
{
    libint2::initialize();
}

void libint2_finalize()
{
    libint2::finalize();
}

std::vector<libint2::Atom> get_atoms(std::string& inp)
{
    std::ifstream input_file(inp);
    std::vector<libint2::Atom> atoms = libint2::read_dotxyz(input_file);
    return atoms;
}

libint2::BasisSet make_basis(std::string bname, std::string fname)
{
    auto atoms = get_atoms(fname);
    libint2::BasisSet obs(bname,atoms);
    return obs;
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
        return this->Atoms;
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
    BasisSet(std::string bname, std::string fname) { 
        this->basis = make_basis(bname, fname);
    }
    BasisSet(std::string bname, std::vector<libint2::Atom> atoms) {
        libint2::BasisSet bas(bname, atoms);
        this->basis = bas;
    }
    BasisSet(std::string bname, Molecule mol) {
        libint2::BasisSet bas(bname,mol.atoms);
        this->basis = bas;
    }
    libint2::BasisSet basis;
    auto print_out() {
        std::copy(begin(this->basis),end(this->basis),
                  std::ostream_iterator<libint2::Shell>(std::cout, "\n"));
    }
    auto getsize() {
        return this->basis.size();
    }
    int max_nprim() {
        return this->basis.max_nprim();
    }
    int max_l() {
        return this->basis.max_l();
    }
};

struct OverlapEngine
{
    OverlapEngine(int max_nprim, int max_l) {
        this->engine = make_engine(libint2::Operator::overlap,max_nprim,max_l);
    }
    libint2::Engine engine;
    auto compute(int s1, int s2, BasisSet& obs) {
        const auto& buf_vec = this->engine.results();
        this->engine.compute(obs.basis[s1],obs.basis[s2]);
        auto n1 = obs.basis[s1].size();
        auto n2 = obs.basis[s2].size();
        auto ints_shellset = buf_vec[0];
        jlcxx::Array<double> ints;
        for(auto f1=0; f1<n1; ++f1)
            for(auto f2=0; f2<n2; ++f2)
                ints.push_back(ints_shellset[f1*n2+f2]);
        return ints;
    }
    auto getsize(BasisSet& obs) {
        int d1 = 0;
        for(int n1=0; n1<obs.basis.size(); n1++) {
            d1 += obs.basis[n1].size();
        }
        return d1;
    }
    auto chunk(int s1, int s2, BasisSet& obs) {
        jlcxx::Array<int> dims;
        dims.push_back(obs.basis[s1].size());
        dims.push_back(obs.basis[s2].size());
        return dims;
    }
    auto startpoint(int s1, int s2, BasisSet& obs) {
        auto shell2bf = obs.basis.shell2bf();
        jlcxx::Array<int> coords;
        coords.push_back(shell2bf[s1]);
        coords.push_back(shell2bf[s2]);
        return coords;
    }
};
struct KineticEngine 
{
    KineticEngine(int max_nprim, int max_l) {
        this->engine = make_engine(libint2::Operator::kinetic,max_nprim,max_l);
    }
    libint2::Engine engine;
    auto compute(int s1, int s2, BasisSet& obs) {
        const auto& buf_vec = this->engine.results();
        this->engine.compute(obs.basis[s1],obs.basis[s2]);
        auto n1 = obs.basis[s1].size();
        auto n2 = obs.basis[s2].size();
        auto ints_shellset = buf_vec[0];
        jlcxx::Array<double> ints;
        for(auto f1=0; f1<n1; ++f1)
            for(auto f2=0; f2<n2; ++f2)
                ints.push_back(ints_shellset[f1*n2+f2]);
        return ints;
    }
    auto getsize(BasisSet& obs) {
        int d1 = 0;
        for(int n1=0; n1<obs.basis.size(); n1++) {
            d1 += obs.basis[n1].size();
        }
        return d1;
    }
    auto chunk(int s1, int s2, BasisSet& obs) {
        jlcxx::Array<int> dims;
        dims.push_back(obs.basis[s1].size());
        dims.push_back(obs.basis[s2].size());
        return dims;
    }
    auto startpoint(int s1, int s2, BasisSet& obs) {
        auto shell2bf = obs.basis.shell2bf();
        jlcxx::Array<int> coords;
        coords.push_back(shell2bf[s1]);
        coords.push_back(shell2bf[s2]);
        return coords;
    }
};
struct NuclearEngine 
{
    NuclearEngine(int max_nprim, int max_l, Molecule mol) {
        libint2::Engine engine(libint2::Operator::nuclear, max_nprim, max_l);
        engine.set_params(libint2::make_point_charges(mol.atoms));
        this->engine = engine;
    }
    auto compute(int s1, int s2, BasisSet& obs) {
        const auto& buf_vec = this->engine.results();
        this->engine.compute(obs.basis[s1],obs.basis[s2]);
        auto n1 = obs.basis[s1].size();
        auto n2 = obs.basis[s2].size();
        auto ints_shellset = buf_vec[0];
        jlcxx::Array<double> ints;
        for(auto f1=0; f1<n1; ++f1)
            for(auto f2=0; f2<n2; ++f2)
                ints.push_back(ints_shellset[f1*n2+f2]);
        return ints;

    }
    auto chunk(int s1, int s2, BasisSet& obs) {
        jlcxx::Array<int> dims;
        dims.push_back(obs.basis[s1].size());
        dims.push_back(obs.basis[s2].size());
        return dims;
    }
    auto startpoint(int s1, int s2, BasisSet& obs) {
        auto shell2bf = obs.basis.shell2bf();
        jlcxx::Array<int> coords;
        coords.push_back(shell2bf[s1]);
        coords.push_back(shell2bf[s2]);
        return coords;
    }
    libint2::Engine engine;
};
struct ERIEngine
{
    ERIEngine(int max_nprim, int max_l) {
        this->engine = make_engine(libint2::Operator::coulomb,
                                    max_nprim,
                                    max_l);
    }
    libint2::Engine engine;
    auto compute(int s1, int s2, int s3, int s4, BasisSet& obs) {
        const auto& buf_vec = this->engine.results();
        this->engine.compute(obs.basis[s1],obs.basis[s2],obs.basis[s3],obs.basis[s4]);
        auto n1 = obs.basis[s1].size();
        auto n2 = obs.basis[s2].size();
        auto n3 = obs.basis[s3].size();
        auto n4 = obs.basis[s4].size();
        auto ints_shellset = buf_vec[0];
        jlcxx::Array<double> ints;
        if (ints_shellset == nullptr) {
            double z = 0.0;
            for(auto f=0; f<(n1*n2*n3*n4); ++f)
                ints.push_back(z);
        }
        else {
            for(auto f=0; f<(n1*n2*n3*n4); ++f)
                ints.push_back(ints_shellset[f]);
        }
        return ints;
    }
    auto chunk(int s1, int s2, int s3, int s4, BasisSet& obs) {
        jlcxx::Array<int> dims;
        dims.push_back(obs.basis[s1].size());
        dims.push_back(obs.basis[s2].size());
        dims.push_back(obs.basis[s3].size());
        dims.push_back(obs.basis[s4].size());
        return dims;
    }
    auto startpoint(int s1, int s2, int s3, int s4, BasisSet& obs) {
        auto shell2bf = obs.basis.shell2bf();
        jlcxx::Array<int> coords;
        coords.push_back(shell2bf[s1]);
        coords.push_back(shell2bf[s2]);
        coords.push_back(shell2bf[s3]);
        coords.push_back(shell2bf[s4]);
        return coords;
    }

};


JLCXX_MODULE Libint2(jlcxx::Module& mod)
{
    mod.method("libint2_init",&libint2_init);
    mod.method("libint2_finalize",&libint2_finalize);
    //mod.method("make_basis",&make_basis);
    mod.add_type<Atom>("Atom")
        .constructor<int,double,double,double>()
        .method("Z",&Atom::Z)
        .method("get_pos",&Atom::get_pos)
        .method("set_pos",&Atom::set_pos);

    mod.add_type<Molecule>("Molecule")
        .constructor<std::string&>()
//        .method("get_atoms",&Molecule::get_atoms)
//        
        .method("get_Atom",&Molecule::get_Atom)
        .method("get_Atoms",&Molecule::get_Atoms)
        .method("get_size",&Molecule::get_size)
        .method("push_back",&Molecule::push_back);

    mod.add_type<BasisSet>("BasisSet")
        .constructor<std::string&, std::string&>()
        .constructor<std::string&, Molecule>()
        .method("getsize",&BasisSet::getsize)
        .method("print_out",&BasisSet::print_out)
        .method("max_nprim",&BasisSet::max_nprim)
        .method("max_l",&BasisSet::max_l);
        
    mod.add_type<OverlapEngine>("OverlapEngine")
        .constructor<int, int>()
        .method("compute",&OverlapEngine::compute)
        .method("getsize",&OverlapEngine::getsize)
        .method("chunk",&OverlapEngine::chunk)
        .method("startpoint",&OverlapEngine::startpoint);

    mod.add_type<NuclearEngine>("NuclearEngine")
        .constructor<int,int,Molecule>()
        .method("compute",&NuclearEngine::compute)
        .method("startpoint",&NuclearEngine::startpoint)
        .method("chunk",&NuclearEngine::chunk);

    mod.add_type<KineticEngine>("KineticEngine")
        .constructor<int,int>()
        .method("compute",&KineticEngine::compute)
        .method("startpoint",&KineticEngine::startpoint)
        .method("chunk",&KineticEngine::chunk);

    mod.add_type<ERIEngine>("ERIEngine")
        .constructor<int,int>()
        .method("compute",&ERIEngine::compute)
        .method("startpoint",&ERIEngine::startpoint)
        .method("chunk",&ERIEngine::chunk);

}
