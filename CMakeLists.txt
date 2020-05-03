cmake_minimum_required(VERSION 3.15)
project(SomeNumberAlgorithm C)

set(CMAKE_C_STANDARD 11)

add_executable(SomeNumberAlgorithm main.c c11exponent.c c11exponent.h c13Lucas.c c13Lucas.h c14square.c c14square.h util.c util.h)