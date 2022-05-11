#pragma once

#include "Shader.h"

class Drawable abstract 
{
protected:
	float* vertices;
	Shader* shader;
	unsigned int VAO;
	void initialiseShader(const char*, const char*);
public:
	Drawable(float[], const char*, const char*);
	void draw();
};