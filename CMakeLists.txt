cmake_minimum_required(VERSION 3.20)
project(dsa VERSION 0.1.0 LANGUAGES CXX)

add_library(dsa INTERFACE)
add_library(dsa::dsa ALIAS dsa)

target_include_directories(
	dsa INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(dsa INTERFACE cxx_std_20)

option(DSA_BUILD_TESTS "Build tests for dsa" ${PROJECT_IS_TOP_LEVEL})
if(DSA_BUILD_TESTS)
    include(CTest)
	add_subdirectory(tests)
endif()

