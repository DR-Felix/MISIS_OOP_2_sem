cmake_minimum_required (VERSION 3.8)

project (rational)
set(CMAKE_CXX_STANDARD 17) #ставим версию CMake

add_executable (main main.cpp) #создаем exe-шник
add_subdirectory(rational)
target_link_libraries(main rat) #подключаем в rat_test библиотеку rat


