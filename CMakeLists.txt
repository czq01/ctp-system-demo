cmake_minimum_required(VERSION 3.1.8)
project(ctp VERSION 0.1.0)

include(CTest)
enable_testing()

# Camke Compile Rules Are Designed As Below.
# //@ Self-Design Area = Start

# 编译C++版本
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX20_STANDARD_COMPILE_OPTION "-std:c++latest")
set(CMAKE_CXX20_EXTENSION_COMPILE_OPTION "-std:c++latest")

# 编译输出位置设置
foreach (TYPE IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${TYPE} TYPE)
    set(EXE_OUTPUT "CMAKE_RUNTIME_OUTPUT_DIRECTORY_${TYPE}")
    set(LIB_OUTPUT "CMAKE_LIBRARY_OUTPUT_DIRECTORY_${TYPE}")
    cmake_language(CALL "set" ${EXE_OUTPUT} "../bin")
    cmake_language(CALL "set" ${LIB_OUTPUT} "../tmp")
endforeach()

# 配置文件路径设置
set(INI_PATH "config.ini")

# 宏定义设置
# _SERVER_RUNTIME_MODE: 0 backtest 1 sim&real
add_compile_definitions(
    _SERVER_RUNTIME_MODE=1
    MAX_SID=64
    WIN32_LEAN_AND_MEAN
)

# dll及ini配置文件拷贝
file(GLOB DLLS_PATH ./lib/*.dll)
file(COPY ${DLLS_PATH} DESTINATION ../bin)
file(COPY ${INI_PATH} DESTINATION ../bin)

# lib链接路径
link_directories(
    ./lib
    ./bin
)

# 头文件路径
include_directories(
    ./include
    ./include/**
)

# 编译过程配置
link_libraries(libmysql WS2_32)

add_library(datetime STATIC src/datetime.cpp)
add_library(base STATIC src/base.cpp)
target_link_libraries(base datetime)

add_library(jsoncpp STATIC src/jsoncpp.cpp src/convert.cpp)
link_libraries(base jsoncpp)

add_library(service STATIC src/service_engine.cpp
    src/CustomMdSpi.cpp src/CustomTradeSpi.cpp
    src/FakeMdSpi.cpp src/FakeTradeSpi.cpp )
add_library(client STATIC src/templete.cpp src/engine.cpp strategy.cpp)

add_executable(service_main service_main.cpp)
add_executable(client_main client_main.cpp)

target_link_libraries(service_main service)
target_link_libraries(client_main client)
target_link_libraries(service thostmduserapi_se thosttraderapi_se WinDataCollect qdmdapi qdptraderapi)

# //@ Self-Design Area = End

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
