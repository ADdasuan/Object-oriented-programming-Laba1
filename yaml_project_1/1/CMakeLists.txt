cmake_minimum_required(VERSION 3.16)
project(yaml_project_1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")


add_executable(yaml_project_1
        src/main.cpp
        src/yaml.cpp
        src/dialog.cpp
        include/input.h
        src/input.cpp
)

target_include_directories(yaml_project_1 PRIVATE include)