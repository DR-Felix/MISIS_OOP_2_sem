<<<<<<< HEAD
add_library(matrixs matrixs.cpp include/matrixs/matrixs.hpp)
set_property(TARGET matrixs PROPERTY CXX_STANDARD 20)
target_include_directories(matrixs PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS matrixs)
||||||| empty tree
=======
add_library(matrixs matrixs.cpp include/matrixs/matrixs.hpp)
set_property(TARGET matrixs PROPERTY CXX_STANDARD 20)
target_include_directories(matrixs PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS matrixs)
>>>>>>> d41395efa836f5c7d767c2452853c96d33f87cda
