cmake_minimum_required(VERSION 3.20)

project(dsa VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Habilitar CTest para poder ejecutar 'make test' o 'ctest'
enable_testing()

# Añadir las subcarpetas
add_subdirectory(lib)
add_subdirectory(test)
