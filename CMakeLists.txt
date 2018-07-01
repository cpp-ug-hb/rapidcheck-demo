cmake_minimum_required(VERSION 3.0)
project(rapidcheck-demo)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(rapidcheck)

function(add_rapidcheck_executable name)
  add_executable(${name} ${name}.cpp ${ARGN})
  target_link_libraries(${name} rapidcheck)
endfunction()

add_rapidcheck_executable(flat_map_1)
add_rapidcheck_executable(flat_map_2)

add_rapidcheck_executable(encoder_1)
add_rapidcheck_executable(mergesort_1)
