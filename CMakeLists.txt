cmake_minimum_required(VERSION 3.15)
project(chaitest)

set(CMAKE_CXX_STANDARD 14)
find_package(pthread)
find_package(dl)
add_subdirectory(deps/ChaiScript)

add_executable(chaitest main.cpp)
target_include_directories(chaitest
    PRIVATE
        deps/ChaiScript/include
)
target_link_libraries(chaitest
    PRIVATE
        parser
        stdlib
        dl
        pthread
)
