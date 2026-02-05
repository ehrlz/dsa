# dsa

Data structures and algorithms implemented in C++.
This repository started following the idea to explore the implementation and concepts of the C++ STL.

There are some personal preferences and designs that doesn't pretend to be useful for others.

## Building
```
cmake -DCMAKE_CXX_COMPILER=clang++ -DBUILD_TESTING=true -B build 
```
> Use `-DBUILD_TESTING=true` for building tests

```
cmake --build build
```

## Testing

[GTest](https://github.com/google/googletest) is used for testing:

```
ctest --output-on-failure --test-dir build
```
