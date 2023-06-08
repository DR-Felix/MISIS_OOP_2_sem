add_library(niblack niblack.cpp include/niblack/niblack.hpp)
target_compile_features(niblack PUBLIC cxx_std_20)
target_include_directories(niblack PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(niblack PUBLIC ${OpenCV_LIBS})
if(NIBLACK_INSTALL_TARGET)
	install(TARGETS niblack DESTINATION bin)
endif()
