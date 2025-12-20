#include <stdlib.h>


typedef struct
{
	void **data; // data stored in heap
	size_t size; // actual elements
	size_t capacity; // max capacity
	size_t element_size;
} vector_t;


vector_t* vector_create(size_t initial_capacity, size_t element_size);

void vector_free(vector_t* vec);

void vector_push_back(vector_t* vec, void *element);

