#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../Core/System.hpp"
#include "../Core/Shader.hpp"

class RenderSystem : public System
{
public:
	void Init();
	void Update(float dt);
	void Finish();
private:
	GLFWwindow* window;
};