# dsa

![CI](https://github.com/ehrlz/dsa/actions/workflows/ci.yml/badge.svg)

Data structures and algorithms implemented in C++.
This repository started following the idea to explore the implementation and concepts of the C++ STL.

There are some personal preferences and designs that doesn't pretend to be useful for others.


## Building

Configure and build:
```bash
cmake --preset debug    # debug
cmake --preset release  # optimized
cmake --preset asan     # sanitizers
```

Build:
```bash
cmake --build --preset debug
cmake --build --preset release
cmake --build --preset asan
```

## Testing

[GTest](https://github.com/google/googletest) is used for testing:

```
ctest --preset debug
ctest --preset release
ctest --preset asan
```

