#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H


#include "Food.h"
#include "Obstacle.h"
#include "Teleport.h"
#include "PoisonedApple.h"
#include <memory>

class GameObjectFactory {
public:
    enum ObjectType { FOOD, OBSTACLE, TELEPORT, POISONEDAPPLE };

    static std::unique_ptr<GameObject> createObject(ObjectType type) {
        switch (type) {
        case FOOD:
            return std::make_unique<Food>();
        case OBSTACLE:
            return std::make_unique<Obstacle>();
        case TELEPORT:
            return std::make_unique<Teleport>();
        case POISONEDAPPLE:
            return std::make_unique<PoisonedApple>();
        default:
            return nullptr;
        }
    }
};


#endif
