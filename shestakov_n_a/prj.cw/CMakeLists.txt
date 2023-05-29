add_executable(course_test "course_test.cpp")
target_link_libraries(course_test course opencv_core opencv_highgui)
add_test(NAME course_test COMMAND course_test)