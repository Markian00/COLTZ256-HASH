cmake_minimum_required(VERSION 3.27)
project(Coltz256_Hash)

set(CMAKE_CXX_STANDARD 17)

add_library(Coltz256_Hash STATIC ColtzHash.cpp)
