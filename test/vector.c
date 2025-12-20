#include "vector.h"
#include "unity.h"

void setUp(void) {}

void tearDown(void) {}

void test_vector_create_capacity()
{
	vector_t* vec = vector_create(30, sizeof(int));
	TEST_ASSERT_NOT_NULL(vec);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_vector_create_capacity);
	return UNITY_END();
}
