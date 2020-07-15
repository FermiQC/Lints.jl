using Lints
using Test
using NPZ
using Serialization

path = joinpath(dirname(pathof(Lints)),"..","test")

Lints.libint2_init()
mol = Lints.Molecule(joinpath(path,"h2o.xyz"))

bas = Lints.BasisSet("6-31G*",mol)
nprim = Lints.max_nprim(bas)
l = Lints.max_l(bas)
S_engine = Lints.OverlapEngine(nprim,l)
T_engine = Lints.KineticEngine(nprim,l)
V_engine = Lints.NuclearEngine(nprim,l,mol)
eri = [Lints.ERIEngine(nprim,l) for i=1:Threads.nthreads()]

s = Lints.getsize(bas)
sz = Lints.getsize(S_engine,bas)
S = zeros(sz,sz)
T = zeros(sz,sz)
V = zeros(sz,sz)
I = zeros(sz,sz,sz,sz)

Lints.make_2D(S,S_engine,bas)
Lints.make_2D(T,T_engine,bas)
Lints.make_2D(V,V_engine,bas)
Lints.make_ERI(I,eri,bas)
Lints.libint2_finalize()

_S = deserialize("S.dat")
_T = deserialize("T.dat")
_V = deserialize("V.dat")
_I = deserialize("I.dat")

__S = npzread("S.npy")
__T = npzread("T.npy")
__V = npzread("V.npy")
__I = npzread("I.npy")

@test isapprox(S,__S; atol=1E-12)
@test isapprox(T,__T; atol=1E-12)
@test isapprox(V,__V; atol=1E-12)
@test isapprox(I,__I; atol=1E-12)
