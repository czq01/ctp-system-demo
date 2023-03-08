cmake_minimum_required(VERSION 3.0.0)
project(boost_test VERSION 0.1.0)

include(CTest)
include_directories("C:/local/boost_1_80_0")
link_directories("C:/local/boost_1_80_0/libs")
enable_testing()

add_executable(boost_test main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
