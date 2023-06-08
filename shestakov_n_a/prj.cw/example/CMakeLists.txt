add_executable(niblack_example main.cpp)

target_link_libraries(niblack_example PRIVATE niblack)

if(NIBLACK_INSTALL_TARGET)
	install(TARGETS niblack_example DESTINATION bin)
endif()
