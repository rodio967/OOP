#ifndef COLLISIONVISITOR_H
#define COLLISIONVISITOR_H


#include "GameObjectVisitor.h"
#include "Teleport.h"
#include "snakemodel.h"

#include "food.h"
#include "teleport.h"
#include "poisonedapple.h"


class CollisionVisitor : public GameObjectVisitor {
public:
    explicit CollisionVisitor(SnakeModel& snake) : snake_(snake) {}

    void visit(Food& food) override {
        snake_.growSnake();
        snake_.placeElem("Food", food.getIndex());
        snake_.addScore();
    }

    void visit(Teleport& teleport) override {
        for (auto& obj : snake_.getGameObjects()) {
            if (obj->getType() == "Teleport" && snake_.checkTeleports(teleport.getIndex(), obj->getIndex())) {
                snake_.setSnakeHeadPosition(obj->getPosition());
            }
        }
        //snake_.placeElem("Teleport");
        snake_.placeTeleport("Teleport", teleport.getIndex());
    }

    void visit(PoisonedApple& poisonedApple) override {
        snake_.decrease();
        snake_.placeElem("PoisonedApple", poisonedApple.getIndex());
    }
    void visit(Obstacle& obstacle) override {
        snake_.setGameOver();
    }

private:
    SnakeModel& snake_;
};


#endif // COLLISIONVISITOR_H
