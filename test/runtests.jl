using Lints
using TensorOperations
using Test
using Serialization

path = joinpath(dirname(pathof(Lints)),"..","test")
tol = 1E-10

@lints begin
    mol1 = Lints.Molecule(joinpath(path,"h2o.xyz"))
    mol2 = Lints.Molecule([8,1,1],[[0.0,0.0,0.0],
                                   [1.0,0.0,0.0],
                                   [0.0,1.0,0.0]])
    for mol in [mol1,mol2]
        bas = Lints.BasisSet("6-31G*",mol)
        bas_small = Lints.BasisSet("6-31G",mol)
        
        #testing conventional integrals
        S = Lints.make_S(bas)
        T = Lints.make_T(bas)
        V = Lints.make_V(bas)
        I = Lints.make_ERI4(bas)

        _S = deserialize("S.dat")
        _T = deserialize("T.dat")
        _V = deserialize("V.dat")
        _I = deserialize("I.dat")

        @test isapprox(S,_S; atol=tol)
        @test isapprox(T,_T; atol=tol)
        @test isapprox(V,_V; atol=tol)
        @test isapprox(I,_I; atol=tol)
        
        #test for infrequent segfaults (used to occur, never want again).
        #computing 1000X should be enough to catch this error.
        for i=1:1000
            Sp = Lints.make_S(bas)
            Tp = Lints.make_T(bas)
            Vp = Lints.make_V(bas)
            Ip = Lints.make_ERI4(bas)
        end
        
        
        
        
        #test that projector is working
        P = Lints.projector(bas_small,bas)
        
        #test DF integrals
        bas = Lints.BasisSet("CC-PVQZ",mol)
        bas_df = Lints.BasisSet("CC-PVQZ-RIFIT",mol)
        
        I = Lints.make_ERI4(bas)
        J = Lints.make_ERI2(bas_df)
        Pqp = Lints.make_ERI3(bas,bas_df)
        Jh = J^(-1/2)
        @tensor b[Q,p,q] := Pqp[P,p,q]*Jh[P,Q]
        @tensor eri2[p,q,r,s] := b[Q,p,q]*b[Q,r,s]
        @test maximum(abs.(eri2 - I)) < 0.05
        
        bas2 = Lints.BasisSet("aug-cc-pvdz",mol)
        sz = Lints.nao(bas2)
        @test sz == 41
    end
end
