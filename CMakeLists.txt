cmake_minimum_required(VERSION 3.15)
project(FourInARow C)

set(CMAKE_C_STANDARD 90)

add_executable(FourInARow main.c AI.h AI.c constants.h printing.h printing.c)