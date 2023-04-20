add_executable(rational_test rational_test.cpp)
target_link_libraries(rational_test rational doctest::doctest)
add_test(NAME rational_test COMMAND rational_test)

add_executable(arrayd_test arrayd_test.cpp)
target_link_libraries(arrayd_test arrayd doctest::doctest)
add_test(NAME arrayd_test COMMAND arrayd_test)

add_executable(matrixs_test matrixs_test.cpp)
target_link_libraries(matrixs_test matrixs doctest::doctest)
add_test(NAME matrixs_test COMMAND matrixs_test)
