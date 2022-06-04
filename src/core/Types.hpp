#pragma once
#include <cstdint>
#include <bitset>

// ==== Entity Component System ==== //

// Each entity is defined by a simple ID
using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;

 // Each component has a simple ID assigned to it
using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENT_TYPES = 32;

// Each entity has a signature representing which components it has
// (e.g. An entity with signature 0b101, would have components 1 and 3)
using Signature = std::bitset<MAX_COMPONENT_TYPES>;