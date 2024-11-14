#ifndef FOOD_H
#define FOOD_H


#include "GameObject.h"

class Food : public GameObject {
public:
    Food();
    QPoint getPosition() const override;
    void setPosition(const QPoint& pos) override;

private:
    QPoint position;
};

#endif
