add_library(course course.cpp include/course/course.hpp)
set_property(TARGET course PROPERTY CXX_STANDARD 20)
target_include_directories(course PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS course)

target_link_libraries(course PRIVATE opencv_core)