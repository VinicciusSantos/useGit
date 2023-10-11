cmake_minimum_required(VERSION 3.26)
project(use_git C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(use_git
        main.c
        utils.c
        utils.h)
