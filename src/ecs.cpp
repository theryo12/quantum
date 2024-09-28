#include "../include/ecs.hpp"
#include "../include/utils.hpp"

#include <cassert>

// EntityManager implementation
Entity EntityManager::createEntity() {
    LOG_DEBUG("creating new entity");
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