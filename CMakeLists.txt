cmake_minimum_required(VERSION 3.15)
project(chaitest)

set(CMAKE_CXX_STANDARD 14)
#find_package(pthread)
find_package(dl)
find_package(X11)
add_subdirectory(deps/ChaiScript)

add_library(MacroEngine
    src/MacroEngine.cpp
)
target_include_directories(MacroEngine
    PRIVATE
        include
)
target_link_libraries(MacroEngine
    PRIVATE
        X11
)

add_executable(chaitest src/main.cpp)
target_include_directories(chaitest
    PRIVATE
        deps/ChaiScript/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(chaitest
    PRIVATE
        parser
        stdlib
        dl
        pthread
        X11
        MacroEngine
)
