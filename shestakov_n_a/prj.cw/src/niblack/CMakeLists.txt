set (NIBLACK_LIBRARY niblack)

file (GLOB SRC 
        niblack.cpp)

add_library(${NIBLACK_LIBRARY} ${SRC})

# Install library into the ./niblack folder
install(TARGETS ${NIBLACK_LIBRARY}
        LIBRARY DESTINATION niblack
        ARCHIVE DESTINATION niblack
        RUNTIME DESTINATION bin)

# Install library header files
install(DIRECTORY niblack/include/niblack
        DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")

# Install the configuration file for library integration in other CMake projects
configure_file(../../cmake/niblackConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/niblackConfig.cmake @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/niblackConfig.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/niblack)

target_link_libraries(${NIBLACK_LIBRARY} PUBLIC ${OpenCV_LIBS})