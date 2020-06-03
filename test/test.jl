using Lints

Lints.libint2_init()
X = Lints.BasisSet("sto-3g","h2o.xyz")
println(Lints.max_nprim(X),Lints.max_l(X))
Y = Lints.OverlapEngine(Lints.max_nprim(X),Lints.max_l(X))
s = Lints.getsize(Y,X)
S = zeros(s,s)
for _i=1:Lints.getsize(X), _j=_i:Lints.getsize(X)
    i = _i-1
    j = _j-1
    println(i,j)
    sp = Lints.startpoint(Y,i,j,X) .+ 1
    chonk = Lints.chunk(Y,i,j,X) .- 1
    _chonk = chonk .+ 1
    r1 = sp[1]:chonk[1]+sp[1]
    r2 = sp[2]:chonk[2]+sp[2]
    #println(size(S[r1,r2]))
    #println(size(reshape(compute(Y,i,j,X),Tuple(_chonk))))
    S[r1,r2] .= reshape(Lints.compute(Y,i,j,X),Tuple(_chonk))
    S[r2,r1] .= transpose(reshape(Lints.compute(Y,i,j,X),Tuple(_chonk)))
end
println(S)
#print_out(X)
#for i=0:4
#    for j=0:4
#        outp = compute(Y,i,j,X)
#        println(reshape(outp,Tuple(dimensions(Y,i,j,X))))
##        println(outp)
#    end
#end
#println(unsafe_wrap(Array,reinterpret(Ptr{Float64},outp),3))
#libint2_finalize()
Lints.libint2_finalize()
