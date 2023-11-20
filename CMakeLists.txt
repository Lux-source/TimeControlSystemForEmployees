cmake_minimum_required(VERSION 3.26)
project(TimeControlSystemForEmployees C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(TimeControlSystemForEmployees
        main.c
        library.h)
