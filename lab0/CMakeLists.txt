cmake_minimum_required(VERSION 3.26)
project(lab0)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab0 main.cpp
        WordCounter.cpp
        WordCounter.h
        FileHandler.cpp
        FileHandler.h)
