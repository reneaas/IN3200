cmake_minimum_required(VERSION 3.15)
project(problemset_1 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_c_FLAGS} -lm")

add_executable(problemset_1 main.c)
