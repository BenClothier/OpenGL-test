#include "Game.h"
#include <list>
#include <iterator>
#include <iostream>
Game::Game() {}

void Game::start() 
{
	instantiateEntity(0, 0);
}

void Game::update()
{
	for (const auto& entity : entities)
	{
		entity->update();
	}
}

void Game::drawUpdate()
{
	for (const auto& entity : entities)
	{
		entity->draw();
	}
}

void Game::instantiateEntity(float x, float y)
{
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
	};

	Entity* newEntity = new Entity(x, y, vertices, "resources/shaders/sh1.vs", "resources/shaders/sh1.fs");
	entities.push_front(newEntity);
	newEntity->start();
}

void Game::destroyEntity(Entity* entity)
{
	entities.remove(entity);
	delete entity;
}
