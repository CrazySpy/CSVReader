cmake_minimum_required(VERSION 3.17)
project(libtest)

set(CMAKE_CXX_STANDARD 14)

add_executable(CSVDemo main.cpp CSVReader.h)

FIND_LIBRARY(RUNTIME_LIB libCSVReader lib)
target_link_libraries(CSVDemo ${RUNTIME_LIB})