add_executable(example main.cpp)

target_link_libraries(example PRIVATE niblack)
target_link_libraries(example PRIVATE ${OpenCV_LIBS})
