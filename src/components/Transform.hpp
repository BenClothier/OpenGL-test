#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>

struct Transform
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};