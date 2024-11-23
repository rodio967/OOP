#ifndef OBSTACLE_H
#define OBSTACLE_H



#include "GameObject.h"
#include "GameObjectVisitor.h"




class Obstacle : public GameObject {
public:
    Obstacle();
    QPoint getPosition() const override;
    void setPosition(const QPoint& pos) override;
    void accept(GameObjectVisitor& visitor) override {
        visitor.visit(*this);
    }

private:
    QPoint position;
};

#endif // OBSTACLE_H
