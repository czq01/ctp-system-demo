cmake_minimum_required(VERSION 3.0.0)
project(ini_test VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

include_directories("ini")
include(CTest)
enable_testing()

add_executable(ini_test main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
