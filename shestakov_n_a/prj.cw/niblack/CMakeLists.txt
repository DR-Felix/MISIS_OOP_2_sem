add_library(niblack niblack.cpp include/niblack/niblack.hpp)
set_property(TARGET niblack PROPERTY CXX_STANDARD 20)
target_include_directories(niblack PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS niblack)


