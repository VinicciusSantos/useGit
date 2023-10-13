cmake_minimum_required(VERSION 3.26)
project(use_git C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(use_git
        main.c
        usecases/listGitConfigurations.c
        usecases/createGitConfiguration.c
        usecases/useGitConfiguration.c
        domain/entities.h
        utils/helpers.c
        utils/helpers.h
        environment.h
        environment.h
        domain/usecases.h)
