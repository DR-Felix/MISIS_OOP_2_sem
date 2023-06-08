<<<<<<< HEAD
add_executable(rational_test "rational_test.cpp")
target_link_libraries(rational_test rational doctest::doctest)
add_test(NAME rational_test COMMAND rational_test)

add_executable(arrayd_test "arrayd_test.cpp")
target_link_libraries(arrayd_test arrayd doctest::doctest)
add_test(NAME arrayd_test COMMAND arrayd_test)

add_executable(matrixs_test "matrixs_test.cpp")
target_link_libraries(matrixs_test matrixs doctest::doctest)
add_test(NAME matrixs_test COMMAND matrixs_test)

add_executable(arrayt_test "arrayt_test.cpp")
target_link_libraries(arrayt_test arrayt doctest::doctest)
add_test(NAME arrayt_test COMMAND arrayt_test)

add_executable(geo2d_test "geo2d_test.cpp")
target_link_libraries(geo2d_test geo2d doctest::doctest)
add_test(NAME geo2d_test COMMAND geo2d_test)
||||||| empty tree
=======
add_executable(rational_test "rational_test.cpp")
target_link_libraries(rational_test rational doctest::doctest)
add_test(NAME rational_test COMMAND rational_test)

add_executable(arrayd_test "arrayd_test.cpp")
target_link_libraries(arrayd_test arrayd doctest::doctest)
add_test(NAME arrayd_test COMMAND arrayd_test)


add_executable(matrixs_test "matrixs_test.cpp")
target_link_libraries(matrixs_test matrixs doctest::doctest)
add_test(NAME matrixs_test COMMAND matrixs_test)

add_executable(arrayt_test "arrayt_test.cpp")
target_link_libraries(arrayt_test arrayt doctest::doctest)
add_test(NAME arrayt_test COMMAND arrayt_test)

add_executable(course_test "course_test.cpp")
target_link_libraries(course_test course opencv_core opencv_highgui)
add_test(NAME course_test COMMAND course_test)

add_executable(geo2d_test "geo2d_test.cpp")
target_link_libraries(geo2d_test geo2d doctest::doctest)
add_test(NAME geo2d_test COMMAND geo2d_test)
>>>>>>> d41395efa836f5c7d767c2452853c96d33f87cda
