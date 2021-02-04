cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(FunCompiler VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(K_FUNCTION_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE INTERNAL "")

add_executable(FunCompiler 
    main.cpp
)

target_include_directories(FunCompiler PUBLIC ${K_FUNCTION_INCLUDE_DIR})
