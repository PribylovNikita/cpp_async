cmake_minimum_required(VERSION 3.24)
project(cleint)

set(CMAKE_CXX_STANDARD 17)

set(Boost_INCLUDE_DIR C:/Users/npribylov/boost_1_81_0)
set(Boost_LIBRARY_DIR C:/Users/npribylov/boost_1_81_0/libs)
find_package(Boost 1.81.0)
include_directories(${Boost_INCLUDE_DIR})

add_executable(client main.cpp)

target_link_libraries(client ws2_32 wsock32)