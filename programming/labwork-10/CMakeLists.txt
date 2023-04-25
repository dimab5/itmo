cmake_minimum_required(VERSION 3.23)
project(labwork_10)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})
endif()

include(FetchContent)

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba)

FetchContent_MakeAvailable(cpr)

add_executable(labwork_10 main.cpp requests.h interface.h interface.cpp requests.cpp)
target_link_libraries(labwork_10 PRIVATE cpr::cpr)