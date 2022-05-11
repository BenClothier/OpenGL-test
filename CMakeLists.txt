cmake_minimum_required(VERSION 3.20.0)

project(opengl-project)

set(PROJECT_MAIN "src/main.cpp")

add_executable(${PROJECT_NAME} ${PROJECT_MAIN})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

include_directories(src)
add_subdirectory(glad)
add_subdirectory(glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)