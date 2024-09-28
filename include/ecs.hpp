#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <cassert>

using Entity = std::uint32_t;

class EntityManager {
public:
    auto createEntity() -> Entity;
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

    auto getComponent(Entity entity) -> Component& {
        assert(components.find(entity) != components.end() && "Component not found!");
        return components[entity];
    }

    void removeComponent(Entity entity) {
        components.erase(entity);
    }

    [[nodiscard]] auto hasComponent(Entity entity) const -> bool {
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
    auto createEntity() -> Entity {
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
    auto getComponent(Entity entity) -> Component& {
        return getComponentArray<Component>().getComponent(entity);
    }

    // Template function to check for components
    template <typename Component>
    auto hasComponent(Entity entity) -> bool {
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
    auto getComponentArray() -> ComponentArray<Component>& {
        static ComponentArray<Component> array;
        return array;
    }
};

struct TestComponent {
    int testValue;
};