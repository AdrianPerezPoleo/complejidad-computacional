cmake_minimum_required(VERSION 3.20)

project("Pushdown Automaton")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    pushdown_automaton
    src/main.cc
)

target_link_libraries(
    pushdown_automaton
)