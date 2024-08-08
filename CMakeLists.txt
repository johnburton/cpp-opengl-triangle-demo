cmake_minimum_required(VERSION 3.20)
project (triangle)

set(CMAKE_CXX_STANDARD 20)
add_executable(triangle main.cpp)
target_link_libraries(triangle GLEW glfw GL)