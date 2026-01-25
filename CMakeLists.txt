cmake_minimum_required(VERSION 3.16)
project(Demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES "*.cpp")

add_executable(Demo ${SOURCES)
