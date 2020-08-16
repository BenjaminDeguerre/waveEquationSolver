cmake_minimum_required(VERSION 2.6)

project(weSolver)

file(GLOB_RECURSE source_file "src/*cpp")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(EXECUTABLE_OUTPUT_PATH build/bin)
include_directories(include)
include_directories(gnuplot-iostream)

add_executable(weSolver ${source_file})
target_link_libraries(weSolver "-lutil -lboost_iostreams -lboost_system -lboost_filesystem")
