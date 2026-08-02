cmake_minimum_required(VERSION 3.20)
project(dsa)

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

option(ENABLE_SANITIZERS "Enable ASan/UBSan" OFF)
if(ENABLE_SANITIZERS)
    target_compile_options(dsa INTERFACE -fsanitize=address,undefined -fno-omit-frame-pointer -g -O1)
    target_link_options(dsa INTERFACE -fsanitize=address,undefined)
endif()

# tests
option(DSA_BUILD_TESTS "Build tests for dsa" ${PROJECT_IS_TOP_LEVEL})

if(DSA_BUILD_TESTS)
    include(CTest)
	add_subdirectory(tests)
endif()

