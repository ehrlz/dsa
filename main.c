#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	void *data;
	int capacity;
	int length;
} vector;

void vector_init(vector *v, size_t element_size, size_t number_of_elements)
{
	v->data = malloc(element_size * number_of_elements);
	if(v == nullptr)
	{
		exit(1);
	}
	v->capacity = number_of_elements;
}

void vector_free(vector* v)
{
	free(v->data);
}

int main(void)
{
	vector v;
	vector_init(&v, sizeof(int), 30);
	vector_free(&v);
	return 0;
}

