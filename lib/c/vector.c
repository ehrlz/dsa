#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

vector_t* vector_create(size_t initial_capacity, size_t element_size)
{
	vector_t* vec = malloc(sizeof(vector_t));
	vec->data = malloc(sizeof(void *)*initial_capacity);
	vec->size = 0;
	vec->capacity = initial_capacity;
	vec->element_size = element_size;
	return vec;
}

void vector_free(vector_t* vec)
{
	// free data memory
	for(size_t i = 0; i < vec->size; i++)
	{
		free(vec->data[i]);
	}
	free(vec->data);
	free(vec);
}

void ensure_capacity(vector_t *vec)
{
	// if the reserved memory is not enough, more is asked and the data is copied
	if(vec->size >= vec->capacity)
	{
		void* new_memory_slot = realloc(vec->data, vec->capacity*2);
	}
}

void vector_push_back(vector_t* vec, void *element)
{
	// Validation
	if(!vec || !element)
		return;
	// Check if the reserved memory is enough
	ensure_capacity(vec);

	// Reserve memory for the new element and copy
	void* new_element = malloc(vec->element_size);
	memcpy(new_element, element, vec->element_size);
	vec->data[vec->size++] = new_element;
}

