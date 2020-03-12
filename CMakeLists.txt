cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(FunCompiler VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(FunCompiler 
    main.cpp
    kfunction.h
)

