#include <cstddef>
#include <cstdlib>

namespace sda
{

template<typename T> class Vector
{

public:

	Vector(std::size_t size_)
		: size(size_)
	{
		data = malloc(size);
	}

	~Vector()
	{
		free(data);
	}

private:
	void *data;					// data stored in the heap
	std::size_t size;			// actual elements
	std::size_t capacity; // max reserved capacity
};

}

