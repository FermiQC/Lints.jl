using CxxWrap
using libint_jll
using Eigen_jll

pref = CxxWrap.prefix_path()
path = libint_jll.Libint2_path
eig_inc  = joinpath(Eigen_jll.artifact_dir,"include/eigen3")

run(`rm -rf CMakeCache.txt CMakeFiles lib/libLints."*"`)
run(pipeline(`sed "s|JLLPATH|$path|g" _CMakeLists.txt`,`tee CMakeLists.txt`))
run(`sed -i "s|EIGENPATH|$eig_inc|g" CMakeLists.txt`)
run(`cmake -DCMAKE_PREFIX_PATH=$pref .`)
run(`cmake --build .`)
