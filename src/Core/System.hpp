#pragma once

#include <set>

#include "Types.hpp"

// Any functionality that iterates upon a list of entities with a certain signature of components
class System
{
public:
	std::set<Entity> entities;
};