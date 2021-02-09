cmake_minimum_required(VERSION 3.0)

project(kfunction_tests)

#set(gtest_disable_pthreads OFF "" FORCE)
option(gtest_disable_pthreads ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (MSVC)
    message("This is MSVC compiler, set Force Shared CRT")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

add_subdirectory(gtest)
include_directories(
    ${gtest_SOURCE_DIR}/include 
    ${K_FUNCTION_INCLUDE_DIR}
)

set(SOURCES
    main.cpp
    test_functions.h
    test_types.h
    tst_operations.h
    tst_sign.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${gtest_SOURCE_DIR}/include
    ${K_FUNCTION_INCLUDE_DIR}
)
target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES} gtest)

set(SOURCES_SECOND
    class_tester.cpp
    testfunction.cpp
    testfunction.h
    test_classes.h
)

add_executable(class_test ${SOURCES_SECOND})
target_include_directories(class_test PUBLIC
    ${gtest_SOURCE_DIR}/include
    ${K_FUNCTION_INCLUDE_DIR}
)
target_link_libraries(class_test ${GTEST_BOTH_LIBRARIES} gtest)

add_test(
    NAME
    ${PROJECT_NAME}
    COMMAND
    ${PROJECT_NAME}
)

add_test(
    NAME class_test
    COMMAND class_test
)
