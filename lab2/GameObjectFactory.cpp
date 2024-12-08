#include "GameObjectFactory.h"
#include "Food.h"
#include "Obstacle.h"
#include "Teleport.h"
#include "PoisonedApple.h"


bool GameObjectFactory::Register(const std::string& id, CreatorFunction creator) {
    return associations_.emplace(id, creator).second;
}


bool GameObjectFactory::Unregister(const std::string& id) {
    return associations_.erase(id) == 1;
}


std::unique_ptr<GameObject> GameObjectFactory::CreateObject(const std::string& id) {
    auto it = associations_.find(id);
    if (it != associations_.end()) {
        return it->second();
    }
    return nullptr;
}


std::unique_ptr<GameObject> CreateFood() {
    return std::make_unique<Food>();
}

std::unique_ptr<GameObject> CreateObstacle() {
    return std::make_unique<Obstacle>();
}

std::unique_ptr<GameObject> CreateTeleport() {
    return std::make_unique<Teleport>();
}

std::unique_ptr<GameObject> CreatePoisonedApple() {
    return std::make_unique<PoisonedApple>();
}
