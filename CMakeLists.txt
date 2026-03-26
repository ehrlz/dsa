cmake_minimum_required(VERSION 3.20)
project(dsa)

set(CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(dsa INTERFACE)
target_include_directories(
	dsa INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(dsa INTERFACE cxx_std_23) # Only this library is compiled with C++23

target_compile_options(dsa INTERFACE
    $<$<CXX_COMPILER_ID:Clang,GNU>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

if(BUILD_TESTING)
	enable_testing()
	add_subdirectory(tests)
endif()

