cmake_minimum_required(VERSION 3.24)
project(blocking_client)

set(CMAKE_CXX_STANDARD 17)
set(Boost_INCLUDE_DIR C:/Users/npribylov/boost_1_81_0) # /path/to/boost_1_81_0
set(Boost_LIBRARY_DIR C:/Users/npribylov/boost_1_81_0/libs) # /path/to/boost_1_81_0/libs
find_package(Boost 1.81.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    add_executable(blocking_client client.cpp)
    target_link_libraries(blocking_client ws2_32 wsock32) # Windows-specific
    add_test(NAME test_3_3 COMMAND blocking_client localhost 3000 3 3)
    add_test(NAME test_10_25 COMMAND blocking_client localhost 3000 10 25)
endif()