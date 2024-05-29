cmake_minimum_required(VERSION 3.5)

project(RK2)

option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(scr STATIC ${CMAKE_CURRENT_SOURCE_DIR}/scr/webpage_button.cpp)
target_include_directories(scr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/scr)

add_executable(main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(scr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/scr)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  file(GLOB SCR_TEST_SOURCES tests/*.cpp)
  add_executable(check ${SCR_TEST_SOURCES})
  target_link_libraries(check scr gtest_main)
  add_test(NAME check COMMAND check)
endif()

include(CPack.cmake)