cmake_minimum_required(VERSION 3.23)
project(labwork_3_dimab5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")


include_directories(.)

add_executable(labwork_3_dimab5
        image.cpp
        image.h
        main.cpp
        main.h
        realization.cpp)
