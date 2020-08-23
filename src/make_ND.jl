function make_2D(destination,engine,basis)
    s = getsize(basis)
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
        @views shell = reshape(buf3[1:Lints.sz(engine)],Tuple(reverse(_chonk)))
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

function make_b(b,engines,basis,dfbasis; precision=Float64)
    s = getsize(basis)
    dfs = getsize(dfbasis)
    maxl = Lints.maxl(engines[1])
    #Threads.@threads for _μ=1:s
    buf1s = [zeros(Int64,3) for i=1:Threads.nthreads()]
    buf2s = [zeros(Int64,3) for i=1:Threads.nthreads()]
    buf3s = [zeros(Float64,maxl^3) for i=1:Threads.nthreads()]
    for i=1:Threads.nthreads()
        Lints.init(engines[i],basis,dfbasis)
    end
    for _μ=1:s
        Threads.@spawn begin
        id = Threads.threadid()
        buf1 = buf1s[id]
        buf2 = buf2s[id]
        buf3 = buf3s[id]
        for _ν=_μ:s
            for _P = 1:dfs
                μ = _μ - 1
                ν = _ν - 1
                P = _P - 1
                Lints.bstartpoint(engines[id],buf1,P,μ,ν,basis,dfbasis) 
                Lints.bchunk(engines[id],buf2,P,μ,ν,basis,dfbasis)
                sp = buf1# .+ 1
                chonk = buf2 #.- 1
                _chonk = chonk #.+ 1
                r1 = sp[1]+1:chonk[1]+sp[1]
                r2 = sp[2]+1:chonk[2]+sp[2]
                r3 = sp[3]+1:chonk[3]+sp[3]
                Lints.compute_b(engines[id],buf3,P,μ,ν,basis,dfbasis)
                ##shell = convert(Array{precision},permutedims(reshape(Lints.bdata(engines[id]),Tuple(reverse(_chonk))),(3,2,1)))
                @views shell = reshape(buf3[1:Lints.bsz(engines[id])],Tuple(reverse(_chonk)))
                b[r3,r2,r1] .= shell
                b[r3,r1,r2] .= permutedims(shell,(1,3,2))
            end
        end
        end
    end
end
function make_j(destination,engine,basis)
    s = getsize(basis)
    buf1 = zeros(Int64,2)
    buf2 = zeros(Int64,2)
    maxl = Lints.maxl(engine)
    buf3 = zeros(Float64,maxl^3)
    for _i=1:s
        for _j=_i:s
            i = _i-1
            j = _j-1
            Lints.jstartpoint(engine,buf1,i,j,basis)
            Lints.jchunk(engine,buf2,i,j,basis)
            sp = buf1 .+ 1
            chonk = buf2 .- 1
            _chonk = chonk .+ 1
            r1 = sp[1]:chonk[1]+sp[1]
            r2 = sp[2]:chonk[2]+sp[2]
            Lints.compute_j(engine,buf3,i,j,basis)
            @views destination[r2,r1] .= reshape(buf3[1:Lints.jsz(engine)],Tuple(reverse(_chonk)))
            destination[r1,r2] .= transpose(destination[r2,r1])
        end
    end
end
function make_ERI(I,engines,basis)
    s = getsize(basis)
    maxl = Lints.maxl(engines[1])
    buf1s = [zeros(Int64,4) for i=1:Threads.nthreads()]
    buf2s = [zeros(Int64,4) for i=1:Threads.nthreads()]
    buf3s = [zeros(Float64,maxl^4) for i=1:Threads.nthreads()]
    for i=1:Threads.nthreads()
        Lints.init(engines[i],basis)
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
                    @views shell = permutedims(reshape(buf3[1:Lints.sz(engines[id])],Tuple(reverse(_chonk))),(4,3,2,1))
                    I[r1,r2,r3,r4] .= shell
                    I[r2,r1,r3,r4] .= permutedims(shell,[2,1,3,4])
                    I[r1,r2,r4,r3] .= permutedims(shell,[1,2,4,3])
                    I[r2,r1,r4,r3] .= permutedims(shell,[2,1,4,3])
                    I[r3,r4,r1,r2] .= permutedims(shell,[3,4,1,2])
                    I[r4,r3,r1,r2] .= permutedims(shell,[4,3,1,2])
                    I[r3,r4,r2,r1] .= permutedims(shell,[3,4,2,1])
                    I[r4,r3,r2,r1] .= permutedims(shell,[4,3,2,1])
                end
            end
        end
    end
end
