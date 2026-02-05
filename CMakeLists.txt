cmake_minimum_required(VERSION 3.10)

project(CppDemoProject)

file(GLOB SOURCES "src/*.cpp" "src/**/*.cpp")

add_executable(Demo ${SOURCES})
