cmake_minimum_required(VERSION 3.20)

project(dsa VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCE_FILES
		main.c
)

add_executable(dsa ${SOURCE_FILES})

target_include_directories(dsa PRIVATE include)

