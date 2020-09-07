function make_S(basis::B;normalize=false) where B <: BasisSet
    make_2D(OverlapEngine,basis,normalize=normalize)
end

function make_T(basis::B;normalize=false) where B <: BasisSet
    make_2D(KineticEngine,basis,normalize=normalize)
end

function make_V(basis::B;normalize=false) where B <: BasisSet
    make_2D(NuclearEngine,basis,normalize=normalize)
end

function make_2D(engine_type,basis;normalize=false) where M <: Molecule
    sz = nao(basis)
    X = zeros(Float64,sz,sz)
    nprim = max_nprim(basis)
    l = max_l(basis)
    if engine_type == NuclearEngine
        mol = get_mol(basis)
        engine = engine_type(nprim,l,mol)
    else
        engine = engine_type(nprim,l)
    end
    make_2D!(X,engine,basis,normalize=normalize)
    X
end
    
function make_2D!(destination,engine,basis;normalize=false)
    s = Lints.nshell(basis)
    if normalize
        Lints.normalize(engine)
    end
    maxl = Lints.maxl(engine)
    buf1 = zeros(Int64,2)
    buf2 = zeros(Int64,2)
    buf3 = zeros(Float64,maxl^2)
    Lints.init(engine,basis,basis)
    for _i=1:s, _j=_i:s
        i = _i-1
        j = _j-1
        Lints.startpoint(engine,buf1,i,j,basis,basis)
        Lints.chunk(engine,buf2,i,j,basis,basis)
        sp = buf1
        chonk = buf2
        _chonk = chonk
        r1 = sp[1]+1:chonk[1]+sp[1]
        r2 = sp[2]+1:chonk[2]+sp[2]
        Lints.compute(engine,buf3,i,j,basis,basis)
        @views shell = reshape(buf3[1:Lints.bufsz(engine)],Tuple(reverse(_chonk)))
        destination[r2,r1] .= shell
        destination[r1,r2] .= transpose(destination[r2,r1])
    end
end

#function make_μ(engine,basis)
#    s = getsize(basis)
#    sz = nao(basis)
#    μx = zeros(Float64,nao,nao)
#    μy = zeros(Float64,nao,nao)
#    μz = zeros(Float64,nao,nao)
#    for _i=1:s, _j=_i:s
#        i = _i-1
#        j = _j-1
#        sp = Lints.startpoint(engine,i,j,basis,basis) .+ 1
#        chonk = Lints.chunk(engine,i,j,basis,basis) .- 1
#        _chonk = chonk .+ 1
#        r1 = sp[1]:chonk[1]+sp[1]
#        r2 = sp[2]:chonk[2]+sp[2]
#
#        Lints.compute(engine,i,j,basis,basis)
#
#        μx[r2,r1] .= reshape(Lints.get_mux(engine),Tuple(reverse(_chonk)))
#        μx[r1,r2] .= transpose(μx[r2,r1])
#
#        μy[r2,r1] .= reshape(Lints.get_muy(engine),Tuple(reverse(_chonk)))
#        μy[r1,r2] .= transpose(μy[r2,r1])
#
#        μz[r2,r1] .= reshape(Lints.get_muz(engine),Tuple(reverse(_chonk)))
#        μz[r1,r2] .= transpose(μz[r2,r1])
#    end
#    μx,μy,μz
#end

function make_ERI4(basis; nt=Threads.nthreads(), normalize=false)
    nprim = max_nprim(basis)
    l = max_l(basis)
    engines = [ERI4Engine(nprim,l) for i=1:nt]
    sz = nao(basis)
    I = zeros(Float64,sz,sz,sz,sz)
    make_4D(I,engines,basis,normalize=normalize)
    I
end
function make_4D(X,engines,basis;normalize=false)
    s = Lints.nshell(basis)
    maxl = Lints.maxl(engines[1])
    buf1s = [zeros(Int64,4) for i=1:Threads.nthreads()]
    buf2s = [zeros(Int64,4) for i=1:Threads.nthreads()]
    buf3s = [zeros(Float64,maxl^4) for i=1:Threads.nthreads()]
    for i=1:Threads.nthreads()
        Lints.init(engines[i],basis)
        if normalize
            Lints.normalize(engines[i])
        end
    end
    Threads.@threads for _ν=1:s
        id = Threads.threadid()
        buf1 = buf1s[id]
        buf2 = buf2s[id]
        buf3 = buf3s[id]
        for _μ=_ν:s
            for _σ=1:s
                for _λ=_σ:s
                    if _μ*(_μ+1)/2 + _ν < _λ*(_λ+1)/2 + _σ
                        continue
                    end
                    μ = _μ - 1
                    ν = _ν - 1
                    λ = _λ - 1
                    σ = _σ - 1
                    Lints.startpoint(engines[id],buf1,μ,ν,λ,σ,basis) 
                    Lints.chunk(engines[id],buf2,μ,ν,λ,σ,basis) 
                    sp = buf1
                    chonk = buf2
                    _chonk = chonk 
                    r1 = sp[1]+1:chonk[1]+sp[1]
                    r2 = sp[2]+1:chonk[2]+sp[2]
                    r3 = sp[3]+1:chonk[3]+sp[3]
                    r4 = sp[4]+1:chonk[4]+sp[4]
                    Lints.compute(engines[id],buf3,μ,ν,λ,σ,basis)
                    #shell = convert(Array{precision},permutedims(reshape(Lints.data(engines[id]),Tuple(reverse(_chonk))),(4,3,2,1)))
                    @views shell = permutedims(reshape(buf3[1:Lints.bufsz(engines[id])],Tuple(reverse(_chonk))),(4,3,2,1))
                    X[r1,r2,r3,r4] .= shell
                    X[r2,r1,r3,r4] .= permutedims(shell,[2,1,3,4])
                    X[r1,r2,r4,r3] .= permutedims(shell,[1,2,4,3])
                    X[r2,r1,r4,r3] .= permutedims(shell,[2,1,4,3])
                    X[r3,r4,r1,r2] .= permutedims(shell,[3,4,1,2])
                    X[r4,r3,r1,r2] .= permutedims(shell,[4,3,1,2])
                    X[r3,r4,r2,r1] .= permutedims(shell,[3,4,2,1])
                    X[r4,r3,r2,r1] .= permutedims(shell,[4,3,2,1])
                end
            end
        end
    end
end

function make_ERI3(basis,dfbasis; nt=Threads.nthreads(), normalize=false)
    sz = nao(basis)
    dfsz = nao(dfbasis)
    Pqp = zeros(Float64,dfsz,sz,sz)
    nprim = max(max_nprim(basis),max_nprim(dfbasis))
    l = max(max_l(basis),max_l(dfbasis))
    engines = [ERI3Engine(nprim,l) for i=1:nt]
    make_3D(Pqp,engines,basis,dfbasis,normalize=normalize)
    Pqp
end

function make_3D(X,engines,basis,dfbasis;normalize=false)
    s = nshell(basis)
    dfs = nshell(dfbasis)
    maxl = Lints.maxl(engines[1])
    #Threads.@threads for _μ=1:s
    nt = Threads.nthreads()
    buf1s = Array{Int64}(undef,3*nt)
    buf2s = Array{Int64}(undef,3*nt)
    buf3s = Array{Float64}(undef,nt*maxl^3)
    for i=1:Threads.nthreads()
        Lints.init(engines[i],basis,dfbasis)
        if normalize
            Lints.normalize(engines[i])
        end
    end
    b1ptr = pointer(buf1s)
    b2ptr = pointer(buf2s)
    b3ptr = pointer(buf3s)
    maxl3 = maxl^3
    @sync for _μ=1:s
        Threads.@spawn begin
        id = Threads.threadid()
        sp = Array{Int64}(undef,3)
        chonk = Array{Int64}(undef,3)
        buf3 = Array{Float64}(undef,maxl3)
        engine = engines[id]
        μ = _μ - 1
        for _ν=_μ:s
            ν = _ν - 1
            for _P = 1:dfs
                P = _P - 1
                Lints.startpoint(engine,sp,P,μ,ν,basis,dfbasis) 
                Lints.chunk(engine,chonk,P,μ,ν,basis,dfbasis)
                Lints.compute(engine,buf3,P,μ,ν,basis,dfbasis)
                sp1,sp2,sp3 = sp
                c1,c2,c3 = chonk
                @inbounds @fastmath for m=1:c3
                    for n=1:c2
                        for P=1:c1
                            tmp = buf3[m+(n-1)*c3+(P-1)*c3*c2]
                            X[P+sp1,n+sp2,m+sp3] = tmp
                            X[P+sp1,m+sp3,n+sp2] = tmp
                        end
                    end
                end
            end
        end
        end
    end
end

function make_ERI2(basis; nt=Threads.nthreads(), normalize=false)
    make_2D(ERI2Engine,basis,normalize=normalize)
end


