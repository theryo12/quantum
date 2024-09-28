#include "../include/ecs.hpp"

#include <cassert>

// EntityManager implementation
auto EntityManager::createEntity() -> Entity {
    if (!avaliableEntities.empty()) {
        Entity id = avaliableEntities.back();
        avaliableEntities.pop_back();
        return id;
    }
    return nextEntityId++;
}

void EntityManager::destroyEntity(Entity entity) {
    avaliableEntities.push_back(entity);
}