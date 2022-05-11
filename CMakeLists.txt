cmake_minimum_required(VERSION 3.20.0)

project(opengl-project)

add_executable(${PROJECT_NAME} ./src/main.cpp)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(glad)
add_subdirectory(glfw3)
target_link_libraries(${PROJECT_NAME} glfw)