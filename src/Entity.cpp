#include "Entity.h"
#include "Drawable.h"
#include <iostream>

Entity::Entity(float x, float y, float vertices[], const char* vShaderPath, const char* fShaderPath) : Drawable(vertices,vShaderPath,fShaderPath)
{
	setPositionX(x);
	setPositionY(y);
}

Entity::~Entity() {}

void Entity::start() 
{

}

void Entity::update() 
{

}

void Entity::setPositionX(float x) {
	this->x = x;
}

void Entity::setPositionY(float y) {
	this->y = y;
}

float Entity::getPositionX() {
	return x;
}

float Entity::getPositionY() {
	return y;
}

