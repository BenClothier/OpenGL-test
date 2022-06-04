#pragma once

#include <any>
#include <memory>
#include <unordered_map>

#include "ComponentArray.hpp"
#include "Types.hpp"

class ComponentManager
{
public:
	template<typename T>
	void RegisterComponent()
	{
		const char* typeName = typeid(T).name();
		assert(componentTypes.find(typeName) == componentTypes.end() && "Registering component type more than once.");

        // Add this component type to the type map
		componentTypes.insert({typeName, nextComponentType});

        // Create a ComponentArray pointer and add it to the component-array map
		componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

        // Increment so that the next component registered will be different
		++nextComponentType;
	}

	template<typename T>
	ComponentType GetComponentType()
	{
		const char* typeName = typeid(T).name();
		assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

        // Return the component type - used for signatures
		return componentTypes[typeName];
	}

    // Attach a component to an entity
	template<typename T>
	void AddComponent(Entity entity, T component)
	{
        // Add a component to the component-array for an entity
		GetComponentArray<T>() -> InsertData(entity, component);
	}

    // Remove a component from an entity
	template<typename T>
	void RemoveComponent(Entity entity)
	{
        // Remove the component associated with the entity in the component-array
		GetComponentArray<T>() -> RemoveData(entity);
	}

    // Fetch this entities component
	template<typename T>
	T& GetComponent(Entity entity)
	{
        // Get a reference to the component of type T of an entity from the component-array
		return GetComponentArray<T>() -> GetData(entity);
	}

    // Must be called when an entity is destroyed
	void EntityDestroyed(Entity entity)
	{
        // Notify every component array that the entity has been destroyed
		for (auto const& pair : componentArrays)
		{
			auto const& component = pair.second;
			component -> EntityDestroyed(entity);
		}
	}

private:
    // Map from type-string-pointers to component types
	std::unordered_map<const char*, ComponentType> componentTypes{};

    // Map from type-string-pointers to component arrays
	std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};

    // The component ID to be assigned to the next registered component
	ComponentType nextComponentType{};

    // Get the pointer to the ComponentArray for type T
	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray()
	{
		const char* typeName = typeid(T).name();
		assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");
		return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
	}
};