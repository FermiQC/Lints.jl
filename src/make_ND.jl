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
    donesies = []
    Threads.@threads for _i=1:s
        id = Threads.threadid()
        for _j=1:s,_k=1:s,_l=1:s
            i = _i - 1
            j = _j - 1
            k = _k - 1
            l = _l - 1
            if [i,j,k,l] in donesies
                continue
            end
            sp = Lints.startpoint(engines[id],i,j,k,l,basis) .+ 1
            chonk = Lints.chunk(engines[id],i,j,k,l,basis) .- 1
            _chonk = chonk .+ 1
            r1 = sp[1]:chonk[1]+sp[1]
            r2 = sp[2]:chonk[2]+sp[2]
            r3 = sp[3]:chonk[3]+sp[3]
            r4 = sp[4]:chonk[4]+sp[4]
            shell = permutedims(reshape(Lints.compute(engines[id],i,j,k,l,basis),Tuple(reverse(_chonk))),(4,3,2,1))
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
    end
end
