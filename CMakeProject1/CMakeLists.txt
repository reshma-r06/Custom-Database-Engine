cmake_minimum_required(VERSION 3.10)
project(MiniDBMS)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add header files directory
include_directories(include)

# Collect all cpp files from src/
file(GLOB SOURCES "src/*.cpp")

# Create executable
add_executable(minidbms ${SOURCES})



