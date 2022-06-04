#pragma once
#include <cstdint>

// Entity Component System
using Entity = std::uint32_t; // Each entity is defined by a simple ID
const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t; // Each component has a simple ID assigned to it
const ComponentType MAX_COMPONENTS = 32;