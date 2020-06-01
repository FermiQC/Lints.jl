module Lints
using CxxWrap
ENV["LD_LIBARY_PATH"] = ENV["LD_LIBRARY_PATH"]*string(@__DIR__)*"/../build/deps/lib/:"
@wrapmodule(joinpath(dirname(pathof(Lints)),"../build/lib/libLints.so"),:Libint2)
end # module
