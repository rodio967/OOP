#ifndef GAMEOBJECTVISITOR_H
#define GAMEOBJECTVISITOR_H

#include "GameObject.h"

class Food;
class Teleport;
class PoisonedApple;
class Obstacle;

class GameObjectVisitor {
public:
    virtual void visit(Food& food) = 0;
    virtual void visit(Teleport& teleport) = 0;
    virtual void visit(PoisonedApple& poisonedApple) = 0;
    virtual void visit(Obstacle& obstacle) = 0;
};

#endif // GAMEOBJECTVISITOR_H
