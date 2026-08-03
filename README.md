# dsa

![CI](https://github.com/ehrlz/dsa/actions/workflows/ci.yml/badge.svg)
![85% coverage](https://github.com/ehrlz/dsa/actions/workflows/coverage-check.yml/badge.svg)

Data structures and algorithms implemented in C++.
This repository started following the idea to explore the implementation and concepts of the C++ STL.

There are some personal preferences and designs that doesn't pretend to be useful for others.


## Building

Configure and build:
```bash
cmake --preset debug    # debug
cmake --preset release  # optimized
cmake --preset asan     # sanitizers
cmake --preset coverage # coverage
```

Build:
```bash
cmake --build --preset debug
cmake --build --preset release
cmake --build --preset asan
cmake --build --preset coverage
```

## Testing

[GTest](https://github.com/google/googletest) is used for testing:

```
ctest --preset debug
ctest --preset release
ctest --preset asan
ctest --preset coverage
```

## CI

Each commit in `main`:
- Compiles in `gcc`
- Compiles in `clang`
- Compiles in `cl` (Windows)
- The whole project has a **85% coverage**

