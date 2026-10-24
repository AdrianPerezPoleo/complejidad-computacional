cmake_minimum_required(VERSION 3.20)

project("Primitive Recursive Functions: Power")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    power
    src/main.cc
    src/program_options.cc
    src/primitive_recursive_function.cc
)

target_link_libraries(
    power
)