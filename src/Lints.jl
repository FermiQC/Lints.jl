__precompile__(false)
module Lints
using CxxWrap
using libint_jll
@wrapmodule(joinpath(dirname(pathof(Lints)),"../deps/lib/libLints"),:Libint2)
function __init__()
    @initcxx
end
ENV["LIBINT_DATA_PATH"] = joinpath(dirname(pathof(Lints)),"../deps/lib/")
include("make_ND.jl")
include("projection.jl")
end # module
