add_executable(check niblack_test.cpp)
target_link_libraries(check niblack doctest::doctest ${OpenCV_LIBS})
add_test(NAME check COMMAND check)
