using CxxWrap
using libint_jll

pref = CxxWrap.prefix_path()
path = libint_jll.Libint2_path

run(`rm -rf CMakeCache.txt CMakeFiles lib/libLints.so`)
run(pipeline(`sed "s|JLLPATH|$path|g" _CMakeLists.txt`,`tee CMakeLists.txt`))
run(`cmake -DCMAKE_PREFIX_PATH=$pref .`)
run(`cmake --build .`)
