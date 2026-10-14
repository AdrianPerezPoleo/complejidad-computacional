cmake_minimum_required(VERSION 3.20)

project("Turing Machine")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    turing-machine-simulator
    src/main.cc
    src/program_options.cc
)

target_link_libraries(
    turing-machine-simulator
)