#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include <memory>
#include <map>
#include <string>
#include "GameObject.h"

class GameObjectFactory {
public:
    using CreatorFunction = std::unique_ptr<GameObject>(*)();

    bool Register(const std::string& id, CreatorFunction creator);
    bool Unregister(const std::string& id);
    std::unique_ptr<GameObject> CreateObject(const std::string& id);

private:
    std::map<std::string, CreatorFunction> associations_;
};


std::unique_ptr<GameObject> CreateFood();
std::unique_ptr<GameObject> CreateObstacle();
std::unique_ptr<GameObject> CreateTeleport();
std::unique_ptr<GameObject> CreatePoisonedApple();

#endif // GAMEOBJECTFACTORY_H
