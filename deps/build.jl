using CxxWrap
using libint_jll
using Eigen_jll
using boost_jll
pref = CxxWrap.prefix_path()
path = dirname(libint_jll.Libint2_path)
eig_inc  = joinpath(Eigen_jll.artifact_dir,"include/eigen3")
boost_inc = joinpath(boost_jll.artifact_dir,"include/")

run(`rm -rf CMakeCache.txt CMakeFiles lib/libLints."*"`)
run(pipeline(`sed "s|JLLPATH|$path|g" _CMakeLists.txt`,`tee CMakeLists.txt`))
#if Sys.isapple()
run(`sed -i"" "s|EIGENPATH|$eig_inc|g" CMakeLists.txt`)
run(`sed -i"" "s|BOOSTPATH|$boost_inc|g" CMakeLists.txt`)
#else
#    run(`sed -i "s|EIGENPATH|$eig_inc|g" CMakeLists.txt`)
#    run(`sed -i "s|BOOSTPATH|$boost_inc|g" CMakeLists.txt`)
run(`cmake -DCMAKE_PREFIX_PATH=$pref .`)
run(`cmake --build .`)
