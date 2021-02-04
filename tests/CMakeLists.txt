cmake_minimum_required(VERSION 3.0)
#test commit
project(kfunction_tests)

set(gtest_disable_pthreads OFF "" FORCE)
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${K_FUNCTION_INCLUDE_DIR})

set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${gtest_SOURCE_DIR}/include
    ${K_FUNCTION_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} gtest)