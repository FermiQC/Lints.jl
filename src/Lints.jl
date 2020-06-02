module Lints
using CxxWrap
@wrapmodule(joinpath(dirname(pathof(Lints)),"../build/lib/libLints.so"),:Libint2)
function __init__()
    @initcxx
end
end # module
