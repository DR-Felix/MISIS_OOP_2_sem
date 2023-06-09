cmake_minimum_required(VERSION 3.21)   

project(Niblack_binarization LANGUAGES CXX)

option(NIBLACK_BUILD_EXAMPLES "Build examples for niblack binarization" ${PROJECT_IS_TOP_LEVEL})
option(NIBLACK_GENERATE_DOCS "Generate documentation for niblack lib" ${PROJECT_IS_TOP_LEVEL})
option(NIBLACK_INSTALL_TARGET "Generate install target for niblack lib" ${PROJECT_IS_TOP_LEVEL})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True) 

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

find_package(OpenCV CONFIG REQUIRED)

if(WIN32)
    set(OpenCV_RUNTIME_PATH "${OpenCV_DIR}/../../bin")
else()
    set(OpenCV_RUNTIME_PATH "${OpenCV_DIR}/../../lib")
endif()


install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/example/images DESTINATION ./bin)

if(NIBLACK_GENERATE_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        set(NIBLACK_DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(NIBLACK_DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile)
        configure_file(${NIBLACK_DOXYGEN_IN} ${NIBLACK_DOXYGEN_OUT})
        add_custom_target(niblack_docs_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${NIBLACK_DOXYGEN_OUT}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs
                COMMENT "Generating API documentation with Doxygen"
                VERBATIM)
        install (DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs
DESTINATION ./)
    else()
        message(STATUS "Couldn't find Doxygen")
    endif()
endif()


if(NIBLACK_INSTALL_TARGET)
    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*opencv_core*"
    )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*opencv_highgui4.dll*"
    )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*opencv_core4*"
    )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*opencv_imgcodecs4*"
    )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*opencv_imgcodecs4*"
    )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*opencv_imgproc4*"
    )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*jpeg62*"
    )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*opencv_videoio4*"
    )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*zlib1*"
    )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*libwebp*"
    )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*libpng16*"
    )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*tiff*"
    )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*libsharpyuv*"
    )

    install(DIRECTORY "${OpenCV_RUNTIME_PATH}/"
      DESTINATION bin
      FILES_MATCHING PATTERN "*liblzma*"
    )

endif()

add_subdirectory(niblack)

if(NIBLACK_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()
