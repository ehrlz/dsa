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
    target_compile_options(dsa INTERFACE -fsanitize=address,undefined)
    target_link_options(dsa INTERFACE -fsanitize=address,undefined)
endif()

# Only test if it is the main project and the variable is enabled
# https://github.com/nlohmann/json/blob/eba0a92bfb1abf242f30e894b96ba11c9f4048c7/CMakeLists.txt#L14
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR AND BUILD_TESTING)
    enable_testing()
	add_subdirectory(tests)
endif()

