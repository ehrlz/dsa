cmake_minimum_required(VERSION 3.20)
project(dsa)

set(CMAKE_CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(dsa INTERFACE)
target_include_directories(
	dsa INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(BUILD_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif()

