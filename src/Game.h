#include "Entity.h"
#include <list>
#pragma once

class Game
{
private:
	std::list<Entity*> entities;
public:
	Game();
	void start();
	void update();
	void drawUpdate();
	void instantiateEntity(float, float);
	void destroyEntity(Entity*);
};

