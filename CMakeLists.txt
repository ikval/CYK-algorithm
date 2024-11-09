cmake_minimum_required(VERSION 3.27)
project(CYK_algorithm)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src)

add_executable(CYK_algorithm
        src/json.hpp
        CFG.cpp
        CFG.h
        main.cpp
        Production.h
        CYK.h
        CYK.cpp
        TableCell.h
        TableCell.cpp
)
