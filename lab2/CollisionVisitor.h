#ifndef COLLISIONVISITOR_H
#define COLLISIONVISITOR_H


#include "GameObjectVisitor.h"
#include "Teleport.h"
#include "snakemodel.h"

class CollisionVisitor : public GameObjectVisitor {
public:
    explicit CollisionVisitor(SnakeModel& snake) : snake_(snake) {}

    void visit(Food& food) override {
        snake_.growSnake();
        snake_.placeFood();
        snake_.addScore();
    }

    void visit(Teleport& teleport) override {
        for (auto& obj : snake_.getGameObjects()) {
            if (auto* otherTeleport = dynamic_cast<Teleport*>(obj.get())) {
                if (otherTeleport != &teleport) {
                    snake_.setSnakeHeadPosition(otherTeleport->getPosition());

                }
            }
        }

        snake_.placeTeleport();
    }

    void visit(PoisonedApple& poisonedApple) override {
        snake_.decrease();
        snake_.placePoisoned_Apple();
    }
    void visit(Obstacle& obstacle) override {
        snake_.setGameOver();
    }

private:
    SnakeModel& snake_;
};


#endif // COLLISIONVISITOR_H
