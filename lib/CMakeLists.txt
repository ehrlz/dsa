# Crear una librería estática a partir de vector.c
add_library(dsa_lib STATIC c/vector.c)

# Indicar dónde están los encabezados (.h)
# PUBLIC permite que los tests también vean la carpeta 'h'
target_include_directories(dsa_lib PUBLIC h)
