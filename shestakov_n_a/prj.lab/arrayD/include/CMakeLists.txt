add_library(array_d array_d.cpp include/array_d/array_d.hpp)
set_property(TARGET array_d PROPERTY CXX_STANDARD 20)
target_include_directories(array_d PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS array_d)