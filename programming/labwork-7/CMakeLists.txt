cmake_minimum_required(VERSION 3.3)
project(labwork-7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(labwork-7 main.cpp Frames.cpp Frames.h)
