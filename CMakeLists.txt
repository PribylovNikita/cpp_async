cmake_minimum_required(VERSION 3.24)
cmake_policy(SET CMP0016 NEW)
project(async_server VERSION 1.0.0 DESCRIPTION "Знакомство с асинхронным вводом/выводом на C++")

set(CMAKE_CXX_STANDARD 17)
set(Boost_INCLUDE_DIR C:/Users/npribylov/boost_1_81_0) # /path/to/boost_1_81_0
set(Boost_LIBRARY_DIR C:/Users/npribylov/boost_1_81_0/libs) # /path/to/boost_1_81_0/libs
find_package(Boost 1.81.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    add_executable(async_server src/async_server/main.cpp)
    target_link_libraries(async_server ws2_32 wsock32) # Windows-specific
    enable_testing()
    add_subdirectory(test)
endif()