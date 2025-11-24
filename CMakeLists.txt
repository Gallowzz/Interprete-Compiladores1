cmake_minimum_required(VERSION 3.15)
project(Interprete)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Interprete src/main.cpp src/lexer.cpp src/parser.cpp)
