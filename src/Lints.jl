module Lints
using CxxWrap
using libint_jll
@wrapmodule(joinpath(dirname(pathof(Lints)),"../deps/lib/libLints.so"),:Libint2)
function __init__()
    @initcxx
end
end # module
