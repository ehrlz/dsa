# Crear el ejecutable de los tests
# Si tienes un unity.c, añádelo aquí también: add_executable(run_tests vector.c unity.c)
add_executable(run_tests 
	vector.c
	unity/unity.c
)

# Enlazar con la librería que creamos en /lib
target_link_libraries(run_tests dsa_lib)

target_include_directories(run_tests PRIVATE unity)

# Registrar el test en el sistema de CTest
add_test(NAME test_vector COMMAND run_tests)
