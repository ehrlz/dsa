include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

add_executable(
	tests
	tests.cpp
)

target_link_libraries(
	tests PRIVATE
	GTest::gtest_main
	dsa
)

gtest_discover_tests(tests)

