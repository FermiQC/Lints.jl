function projector(source,dest)
    nprim = maximum((Lints.max_nprim(source),Lints.max_nprim(dest)))
    l = maximum((Lints.max_l(source),Lints.max_l(dest)))
    engine = Lints.OverlapEngine(nprim,l)
    Lints.init(engine,source,dest)

    s1 = nshell(source)
    s2 = nshell(dest)
    sz1 = nao(source)
    sz2 = nao(dest)
    P = zeros(sz1,sz2)
    maxl = Lints.maxl(engine)
    buf1 = zeros(Int64,2)
    buf2 = zeros(Int64,2)
    buf3 = zeros(Float64,maxl^2)

    for _i=1:s1, _j=1:s2
        i = _i-1
        j = _j-1
        Lints.startpoint(engine,buf1,i,j,source,dest)
        Lints.chunk(engine,buf2,i,j,source,dest)
        sp = buf1
        chonk = buf2
        _chonk = chonk 
        r1 = sp[1]+1:chonk[1]+sp[1]
        r2 = sp[2]+1:chonk[2]+sp[2]
        Lints.compute(engine,buf3,i,j,source,dest)
        P[r1,r2] .= transpose(reshape(buf3[1:bufsz(engine)],Tuple(reverse(_chonk))))
    end
    engine = nothing
    P
end
