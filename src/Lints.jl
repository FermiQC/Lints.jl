module Lints
using CxxWrap
#using Libdl
using libint_jll
@wrapmodule(joinpath(dirname(pathof(Lints)),"../deps/lib/libLints.so"),:Libint2)
function __init__()
    #libint =  dlopen(libint_jll.Libint2_path)
    @initcxx
#    println(libint_jll.Libint2_path)
end
end # module
