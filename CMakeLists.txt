cmake_minimum_required(VERSION 3.31)
project(Vectra)

set(CMAKE_CXX_STANDARD 20)

add_executable(Vectra main.cpp
        Vectra/Engine.cpp
        Vectra/Engine.hpp
        Vectra/Parser.cpp
        Vectra/Parser.hpp
        Vectra/Core.hpp
        Vectra/Core.cpp)
