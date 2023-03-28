cmake_minimum_required(VERSION 3.23)
project(blocking_client)

set(CMAKE_CXX_STANDARD 17)
set(Boost_INCLUDE_DIR /usr/include) # /path/to/<boost>
set(Boost_LIBRARY_DIR /usr/lib) # /path/to/<boost libs>
find_package(Boost 1.71.0)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
    add_executable(blocking_client client.cpp)
    #target_link_libraries(blocking_client ws2_32 wsock32) # Windows-specific
    target_link_libraries(blocking_client boost_system boost_thread pthread) # Linux
    add_test(NAME test_3_3 COMMAND blocking_client localhost 3000 3 3)
    add_test(NAME test_10_25 COMMAND blocking_client localhost 3000 10 25)
endif()