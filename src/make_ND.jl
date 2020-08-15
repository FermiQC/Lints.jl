function make_2D(destination,engine,basis)
    s = getsize(basis)
    for _i=1:s, _j=_i:s
        i = _i-1
        j = _j-1
        sp = Lints.startpoint(engine,i,j,basis,basis) .+ 1
        chonk = Lints.chunk(engine,i,j,basis,basis) .- 1
        _chonk = chonk .+ 1
        r1 = sp[1]:chonk[1]+sp[1]
        r2 = sp[2]:chonk[2]+sp[2]
        destination[r2,r1] .= reshape(Lints.compute(engine,i,j,basis,basis),Tuple(reverse(_chonk)))
        destination[r1,r2] .= transpose(destination[r2,r1])
    end
end

function make_μ(engine,basis)
    s = getsize(basis)
    sz = nao(basis)
    μx = zeros(Float64,nao,nao)
    μy = zeros(Float64,nao,nao)
    μz = zeros(Float64,nao,nao)
    for _i=1:s, _j=_i:s
        i = _i-1
        j = _j-1
        sp = Lints.startpoint(engine,i,j,basis,basis) .+ 1
        chonk = Lints.chunk(engine,i,j,basis,basis) .- 1
        _chonk = chonk .+ 1
        r1 = sp[1]:chonk[1]+sp[1]
        r2 = sp[2]:chonk[2]+sp[2]

        Lints.compute(engine,i,j,basis,basis)

        μx[r2,r1] .= reshape(Lints.mux(engine),Tuple(reverse(_chonk)))
        μx[r1,r2] .= transpose(μx[r2,r1])

        μy[r2,r1] .= reshape(Lints.muy(engine),Tuple(reverse(_chonk)))
        μy[r1,r2] .= transpose(μy[r2,r1])

        μz[r2,r1] .= reshape(Lints.muz(engine),Tuple(reverse(_chonk)))
        μz[r1,r2] .= transpose(μz[r2,r1])
    end
    μx,μy,μz
end

function make_b(b,engines,basis,dfbasis; precision=Float64)
    s = getsize(basis)
    dfs = getsize(dfbasis)
    Threads.@threads for _μ=1:s
        id = Threads.threadid()
        for _ν=1:s
            for _P = 1:dfs
                μ = _μ - 1
                ν = _ν - 1
                P = _P - 1
                sp = Lints.bstartpoint(engines[id],P,μ,ν,basis,dfbasis) .+ 1
                chonk = Lints.bchunk(engines[id],P,μ,ν,basis,dfbasis) .- 1
                _chonk = chonk .+ 1
                r1 = sp[1]:chonk[1]+sp[1]
                r2 = sp[2]:chonk[2]+sp[2]
                r3 = sp[3]:chonk[3]+sp[3]
                shell = convert(Array{precision},permutedims(reshape(Lints.compute_b(engines[id],P,μ,ν,basis,dfbasis),Tuple(reverse(_chonk))),(3,2,1)))
                b[r1,r2,r3] .= shell
            end
        end
    end
end
function make_j(destination,engine,basis)
    s = getsize(basis)
    for _i=1:s, _j=1:s
        i = _i-1
        j = _j-1
        sp = Lints.jstartpoint(engine,i,j,basis) .+ 1
        chonk = Lints.jchunk(engine,i,j,basis) .- 1
        _chonk = chonk .+ 1
        r1 = sp[1]:chonk[1]+sp[1]
        r2 = sp[2]:chonk[2]+sp[2]
        destination[r2,r1] .= reshape(Lints.compute_j(engine,i,j,basis),Tuple(reverse(_chonk)))
    end
end
function make_ERI(I,engines,basis; precision=Float64)
    s = getsize(basis)
    Threads.@threads for _ν=1:s
        id = Threads.threadid()
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
                    sp = Lints.startpoint(engines[id],μ,ν,λ,σ,basis) .+ 1
                    chonk = Lints.chunk(engines[id],μ,ν,λ,σ,basis) .- 1
                    _chonk = chonk .+ 1
                    r1 = sp[1]:chonk[1]+sp[1]
                    r2 = sp[2]:chonk[2]+sp[2]
                    r3 = sp[3]:chonk[3]+sp[3]
                    r4 = sp[4]:chonk[4]+sp[4]
                    shell = convert(Array{precision},permutedims(reshape(Lints.compute(engines[id],μ,ν,λ,σ,basis),Tuple(reverse(_chonk))),(4,3,2,1)))
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
