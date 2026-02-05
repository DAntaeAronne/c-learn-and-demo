cmake_minimum_required(VERSION 3.10)

project(CppDemoProject)

# Automatically collect all .cpp files
file(GLOB SOURCES "src/*.cpp" "src/**/*.cpp")

# Define the executable target
add_executable(Demo ${SOURCES})
