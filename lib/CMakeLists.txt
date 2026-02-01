# Crear una librería estática a partir de vector.c
add_library(dsa_lib STATIC c/vector.c)

target_compile_options(dsa_lib PRIVATE $<$<C_COMPILER_ID:Clang>:-Wall -Wextra -Werror -Weverything>
																	 $<$<C_COMPILER_ID:GCC>:-Wall -Wextra -Werror -Wpedantic>)

# Indicar dónde están los encabezados (.h)
# PUBLIC permite que los tests también vean la carpeta 'h'
target_include_directories(dsa_lib PUBLIC h)
