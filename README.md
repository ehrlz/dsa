# dsa

Data structures and algorithms implemented in C++.
This repository started following the idea to explore the implementation and concepts of the C++ STL.

There are some personal preferences and designs that doesn't pretend to be useful for others.


## Building

Configure and build:
```bash
cmake --preset debug    # debug + sanitizers + tests
cmake --preset release  # optimized
```

Build:
```bash
cmake --build --preset debug
cmake --build --preset release
```

## Testing

[GTest](https://github.com/google/googletest) is used for testing:

```
ctest --preset debug
```
