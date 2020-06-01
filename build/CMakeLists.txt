project(Lints)

cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_BINARY_DIR}/deps/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_CXX_FLAGS "-I/usr/include/eigen3 -L${CMAKE_BINARY_DIR}/deps/lib/")

find_package(JlCxx REQUIRED)
find_package(Libint2 REQUIRED)
find_package(Eigen3 REQUIRED)
get_target_property(JlCxx_location JlCxx::cxxwrap_julia LOCATION)
get_filename_component(JlCxx_location ${JlCxx_location} DIRECTORY)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")

message(STATUS "Found JlCxx at ${JlCxx_location}")

add_library(Lints SHARED ../src/Lints.cpp)

link_directories(${CMAKE_BINARY_DIR}/deps/lib/)
target_link_libraries(Lints JlCxx::cxxwrap_julia)
target_link_libraries(Lints libint2)

install(TARGETS
    Lints
LIBRARY DESTINATION lib
ARCHIVE DESTINATION lib
RUNTIME DESTINATION lib)
