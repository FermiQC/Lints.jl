using Lints
using Test
path = joinpath(dirname(pathof(Lints)),"..","test")

Lints.libint2_init()
mol = Lints.Molecule("h2o.xyz")
bas = Lints.BasisSet("sto-3g",mol)
nprim = Lints.max_nprim(bas)
l = Lints.max_l(bas)
println(nprim,l)
S_engine = Lints.OverlapEngine(nprim,l)
T_engine = Lints.KineticEngine(nprim,l)
V_engine = Lints.NuclearEngine(nprim,l,mol)
eri = Lints.ERIEngine(nprim,l)
println("here")

s = Lints.getsize(bas)
sz = Lints.getsize(S_engine,bas)
println(sz)
S = zeros(sz,sz)
T = zeros(sz,sz)
V = zeros(sz,sz)
I = zeros(sz,sz,sz,sz)
println(size(I))

for _i=1:s, _j=_i:s
    i = _i-1
    j = _j-1
    sp = Lints.startpoint(S_engine,i,j,bas) .+ 1
    chonk = Lints.chunk(S_engine,i,j,bas) .- 1
    _chonk = chonk .+ 1
    println("$i $j")
    r1 = sp[1]:chonk[1]+sp[1]
    r2 = sp[2]:chonk[2]+sp[2]
    S[r1,r2] .= reshape(Lints.compute(S_engine,i,j,bas),Tuple(_chonk))
    S[r2,r1] .= transpose(S[r1,r2])
    T[r1,r2] .= reshape(Lints.compute(T_engine,i,j,bas),Tuple(_chonk))
    T[r2,r1] .= transpose(T[r1,r2])
    V[r1,r2] .= reshape(Lints.compute(V_engine,i,j,bas),Tuple(_chonk))
    V[r2,r1] .= transpose(V[r1,r2])
end
donesies = []
for _i=1:s,_j=1:s,_k=1:s,_l=1:s
    i = _i - 1
    j = _j - 1
    k = _k - 1
    l = _l - 1
    if [i,j,k,l] in donesies
        continue
    end
    sp = Lints.startpoint(eri,i,j,k,l,bas) .+ 1
    chonk = Lints.chunk(eri,i,j,k,l,bas) .- 1
    _chonk = chonk .+ 1
    r1 = sp[1]:chonk[1]+sp[1]
    r2 = sp[2]:chonk[2]+sp[2]
    r3 = sp[3]:chonk[3]+sp[3]
    r4 = sp[4]:chonk[4]+sp[4]
    #println("--")
    #println(size(I[r1,r2,r3,r4]))
    #println(size(permutedims(reshape(Lints.compute(eri,i,j,k,l,bas),Tuple(reverse(_chonk))),(4,3,2,1))))
    #println("--")
    shell = permutedims(reshape(Lints.compute(eri,i,j,k,l,bas),Tuple(reverse(_chonk))),(4,3,2,1))
    I[r1,r2,r3,r4] .= shell
    push!(donesies,[i,j,k,l])
    I[r2,r1,r3,r4] .= permutedims(shell,[2,1,3,4])
    push!(donesies,[j,i,k,l])
    I[r1,r2,r4,r3] .= permutedims(shell,[1,2,4,3])
    push!(donesies,[i,j,l,k])
    I[r2,r1,r4,r3] .= permutedims(shell,[2,1,4,3])
    push!(donesies,[j,i,l,k])
    I[r3,r4,r1,r2] .= permutedims(shell,[3,4,1,2])
    push!(donesies,[k,l,i,j])
    I[r4,r3,r1,r2] .= permutedims(shell,[4,3,1,2])
    push!(donesies,[l,k,i,j])
    I[r3,r4,r2,r1] .= permutedims(shell,[3,4,2,1])
    push!(donesies,[k,l,j,i])
    I[r4,r3,r2,r1] .= permutedims(shell,[4,3,2,1])
    push!(donesies,[l,k,j,i])
end
@test true
#println(I)
#psi4.core.be_quiet()
#mole = psi4.geometry("""
#                     H 0.0 -1.0 0.0
#                     H 0.0 1.0 0.0
#                     symmetry c1
#                     noreorient
#                     """)
#e,wfn = psi4.energy("hf/sto-3g",return_wfn=true)
#mints = psi4.core.MintsHelper(wfn.basisset())
#println(S)
##println(mints.ao_overlap().to_array())
#println("====")
#println(T)
##println(mints.ao_kinetic().to_array())
#println("====")
#println(V)
##println(mints.ao_potential().to_array())
#println("====")
#println(I)
##println(mints.ao_eri().to_array())
Lints.libint2_finalize()
