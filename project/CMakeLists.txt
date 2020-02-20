cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(FunCompiler VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB HEADERS include/*.h)
file(GLOB SOURCES src/*.cpp)

add_executable(FunCompiler 
    main.cpp
    ${HEADERS}
    ${SOURCES}
)

target_include_directories(FunCompiler PRIVATE include)