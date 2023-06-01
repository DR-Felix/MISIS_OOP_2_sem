add_executable(course_test "course_test.cpp")
target_link_libraries(course_test course opencv_core opencv_highgui)
add_test(NAME course_test COMMAND course_test)

add_custom_command(TARGET course_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:course_test> graph.tex
)
