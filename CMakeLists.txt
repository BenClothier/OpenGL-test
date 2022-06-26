cmake_minimum_required(VERSION 3.20.0)

project(opengl-project)

file(GLOB_RECURSE PROJECT_SRC
     "src/*.h"
     "src/*.hpp"
     "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(glm)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glm)