#ifndef FOOD_H
#define FOOD_H


#include "GameObject.h"
#include "GameObjectVisitor.h"



class Food : public GameObject {
public:
    Food();
    QPoint getPosition() const override;
    void setPosition(const QPoint& pos) override;
    void accept(GameObjectVisitor& visitor) override {
        visitor.visit(*this);
    }

private:
    QPoint position;
};

#endif // FOOD_H
