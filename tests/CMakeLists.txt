include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v1.17.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(googletest)

# --- test-only compiler settings, NOT attached to dsa itself ---
add_library(dsa_test_flags INTERFACE)

target_compile_options(dsa_test_flags INTERFACE
    $<$<CXX_COMPILER_ID:GNU>:
        -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor
        -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual
        -Wconversion -Wsign-conversion -Wnull-dereference
        -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough
    >
    $<$<CXX_COMPILER_ID:Clang>:
        -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor
        -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual
        -Wconversion -Wsign-conversion -Wnull-dereference
        -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough
    >
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

option(DSA_ENABLE_SANITIZERS "Enable ASan/UBSan" OFF)
if(DSA_ENABLE_SANITIZERS)
    target_compile_options(dsa_test_flags INTERFACE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-fsanitize=address,undefined -fno-omit-frame-pointer -O1>
    )
    target_link_options(dsa_test_flags INTERFACE
        $<$<CXX_COMPILER_ID:GNU,Clang>:-fsanitize=address,undefined>
    )
endif()

option(DSA_ENABLE_COVERAGE "Enable coverage" OFF)
if(DSA_ENABLE_COVERAGE)
    target_compile_options(dsa_test_flags INTERFACE
        $<$<CXX_COMPILER_ID:GNU,Clang>:--coverage>
    )
    target_link_options(dsa_test_flags INTERFACE
        $<$<CXX_COMPILER_ID:GNU,Clang>:--coverage>
    )
endif()

add_executable(dsa_tests
    vector.cpp
    linked_list.cpp
)
target_link_libraries(dsa_tests PRIVATE
    GTest::gtest_main
    dsa::dsa
    dsa_test_flags
)

include(GoogleTest)
gtest_discover_tests(dsa_tests)

