#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <cassert>

using Entity = std::uint32_t;

class EntityManager {
public:
    Entity createEntity();
    void destroyEntity(Entity entity);

private:
    Entity nextEntityId = 0;
    std::vector<Entity> avaliableEntities;
};

// Component storage for generic components
template <typename Component>
class ComponentArray {
public:
    void addComponent(Entity entity, Component component) {
        components[entity] = std::move(component);
    }

    Component& getComponent(Entity entity) {
        assert(components.find(entity) != components.end() && "Component not found!");
        return components[entity];
    }

    void removeComponent(Entity entity) {
        components.erase(entity);
    }

    bool hasComponent(Entity entity) const {
        return components.find(entity) != components.end();
    }

    template <typename Func>
    void forEach(Func&& func) {
        for (auto& [entity, component] : components) {
            func(entity, component);
        }
    }

private:
    std::unordered_map<Entity, Component> components;
};

// ECS class
class ECS {
public:
    Entity createEntity() {
        return entityManager.createEntity();
    }

    void destroyEntity(Entity entity) {
        entityManager.destroyEntity(entity);
    }

    // Template function to add components
    template <typename Component>
    void addComponent(Entity entity, Component component) {
        getComponentArray<Component>().addComponent(entity, std::move(component));
    }

    // Template function to retrieve components
    template <typename Component>
    Component& getComponent(Entity entity) {
        return getComponentArray<Component>().getComponent(entity);
    }

    // Template function to check for components
    template <typename Component>
    bool hasComponent(Entity entity) {
        return getComponentArray<Component>().hasComponent(entity);
    }

    // Template function to remove components
    template <typename Component>
    void removeComponent(Entity entity) {
        getComponentArray<Component>().removeComponent(entity);
    }

    // Template function to iterate over entities with a specific component type
    template <typename Component, typename Func>
    void forEach(Func&& func) {
        getComponentArray<Component>().forEach(std::forward<Func>(func));
    }

private:
    EntityManager entityManager;

    template <typename Component>
    ComponentArray<Component>& getComponentArray() {
        static ComponentArray<Component> array;
        return array;
    }
};

struct TestComponent {
    int testValue;
};