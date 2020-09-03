__precompile__(false)
module Lints
const libint2_au_to_bohr = 0.529177210903
export @lints
using CxxWrap
using libint_jll
@wrapmodule(joinpath(dirname(pathof(Lints)),"../deps/lib/libLints"),:Libint2)
function __init__()
    @initcxx
end
ENV["LIBINT_DATA_PATH"] = joinpath(dirname(pathof(Lints)),"../deps/lib/")
include("make_ND.jl")
include("projection.jl")

function Molecule(Z::Array{Int,1},pos::Array{Array{Float64,1}})
    @assert length(Z) == size(pos,1) "The lengths of Z (atomic number) and position vectors does not match"
    posvec = vcat(pos...)
    posvec ./= 0.529177210903
    Molecule(Z,posvec)
end

macro lints(expr)
    quote
        Lints.libint2_init()
        $(esc(expr))
        Lints.libint2_finalize()
    end
end

end # module
