cmake_minimum_required(VERSION 3.13)
project(MiniSearchEngine)

set(CMAKE_CXX_STANDARD 14)

add_executable(MiniSearchEngine main.cpp stemmer/porter2_stemmer.h stemmer/porter2_stemmer.cpp stemmer/util/hash.h stemmer/util/string_view.h SearchEngine.h SearchEngine.cpp)