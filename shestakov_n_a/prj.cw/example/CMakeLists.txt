add_executable(niblack_example main.cpp)

target_link_libraries(niblack_example PRIVATE niblack)

if(NIBLACK_INSTALL_TARGET)
	install(TARGETS niblack_example DESTINATION bin)
endif()

add_custom_target(niblack_example_copy_images
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/images
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/images ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/images
    COMMENT "copying images to output dir"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

add_dependencies(niblack_example niblack_example_copy_images)
