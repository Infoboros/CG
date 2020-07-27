cmake_minimum_required(VERSION 3.16)
project(CG C)

set(CMAKE_C_STANDARD 11)

add_executable(CG main.c render/Headers/line.h render/Sources/line.c render/Headers/circle.h render/Sources/circle.c)