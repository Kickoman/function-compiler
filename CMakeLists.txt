cmake_minimum_required(VERSION 3.0)

project(funCompiler)

option(BUILD_TESTS "Build unit tests" ON)

add_subdirectory(kfunction)
if (BUILD_TESTS)
	add_subdirectory(tests)
endif()
