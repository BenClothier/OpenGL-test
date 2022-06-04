#pragma once
#include <cstdint>

// Entity Component System
using Entity = std::uint32_t; // Each entity is defined by a simple ID
const Entity MAX_ENTITIES = 5000;