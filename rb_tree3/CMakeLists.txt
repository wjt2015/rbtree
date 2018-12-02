cmake_minimum_required(VERSION 3.0)
project(rbMain)
set(CMAKE_BUILD_TYPE "Debug")

include_directories("include")
link_directories("lib")
add_subdirectory(lib_src)
add_subdirectory(main_src)
