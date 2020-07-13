function make_2D(destination,engine,basis)
    s = getsize(basis)
    for _i=1:s, _j=_i:s
        i = _i-1
        j = _j-1
        sp = Lints.startpoint(engine,i,j,basis) .+ 1
        chonk = Lints.chunk(engine,i,j,basis) .- 1
        _chonk = chonk .+ 1
        r1 = sp[1]:chonk[1]+sp[1]
        r2 = sp[2]:chonk[2]+sp[2]
        destination[r1,r2] .= reshape(Lints.compute(engine,i,j,basis),Tuple(_chonk))
        destination[r2,r1] .= transpose(destination[r1,r2])
    end
end

function make_ERI(I,engines,basis)
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
                    shell = permutedims(reshape(Lints.compute(engines[id],μ,ν,λ,σ,basis),Tuple(reverse(_chonk))),(4,3,2,1))
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
