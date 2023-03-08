cmake_minimum_required(VERSION 3.0.0)
project(quantlib_test VERSION 0.1.0)

include_directories(
    "C:/Program Files/QuantLib-1.27.1"
    "C:/local/boost_1_80_0"
)
link_directories(
    "C:/Program Files/QuantLib-1.27.1/lib"
    "C:/local/boost_1_80_0/libs"
)

include(CTest)
enable_testing()

add_executable(quantlib_test main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
