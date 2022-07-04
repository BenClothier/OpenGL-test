#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../core/System.hpp"
#include "../core/Shader.hpp"
#include "../core/View.hpp"

class RenderSystem : public System
{
public:
	void Init(View& view);
	void Update(float dt);
	void Finish();
private:
	GLFWwindow* window;
	View view;
};