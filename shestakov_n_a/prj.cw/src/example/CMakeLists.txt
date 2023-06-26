add_executable(niblack_example main.cpp)

# Link libraries
target_link_libraries(niblack_example PRIVATE niblack)
target_link_libraries(niblack_example PRIVATE ${OpenCV_LIBS})

# Set the include directories for hoglib headers
target_include_directories(niblack_example PRIVATE
    ${CMAKE_SOURCE_DIR}/src/niblack/include
)

#Define a constant variable for main.cpp code
target_compile_definitions(niblack_example PRIVATE INSTALL_PATH="${CMAKE_INSTALL_PREFIX}/bin")

#Install hogexe executable into a ./bin folder
install(TARGETS niblack_example RUNTIME DESTINATION ./bin
        COMPONENT Runtime)

#Install all dll dependencies along with executable
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/
        DESTINATION ./bin
        COMPONENT Runtime
        FILES_MATCHING PATTERN "*.dll"
)
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG}/
        DESTINATION ./bin
        COMPONENT Runtime
        FILES_MATCHING PATTERN "*.dll"
)
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/
        DESTINATION ./bin
        COMPONENT Runtime
        FILES_MATCHING PATTERN "*.dll"
)
install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO}/
        DESTINATION ./bin
        COMPONENT Runtime
        FILES_MATCHING PATTERN "*.dll"
)

#Install configuration file and images for main.cpp console application
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/images DESTINATION ./bin)