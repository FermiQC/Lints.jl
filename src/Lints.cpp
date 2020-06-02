#include "jlcxx/jlcxx.hpp"
#include "libint2.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

std::string greet()
{
    return "hello, world";
}

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

struct BasisSet
{
    BasisSet(std::string bname, std::string fname) { 
        this->basis = make_basis(bname, fname);
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
                //ints[f1][f2] = ints_shellset[f1*n2+f2];
        //return ints_shellset;
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
//        auto shell2bf = obs.basis.shell2bf();
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


JLCXX_MODULE define_julia_module(jlcxx::Module& mod)
{
    mod.method("greet",&greet);
}

JLCXX_MODULE Libint2(jlcxx::Module& mod)
{
    mod.method("libint2_init",&libint2_init);
    mod.method("libint2_finalize",&libint2_finalize);
    //mod.method("make_basis",&make_basis);
    mod.add_type<BasisSet>("BasisSet")
        .constructor<std::string&, std::string&>()
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

}
