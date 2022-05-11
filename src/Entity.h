#pragma once

#include "Drawable.h"

class Entity : public Drawable
{
private:
	float x;
	float y;
public:
	Entity(float x, float y, float vertices[], const char* vShaderPath, const char* fShaderPath);
	~Entity();
	virtual void start();
	virtual void update();
	void setPositionX(float);
	void setPositionY(float);
	float getPositionX();
	float getPositionY();
};

