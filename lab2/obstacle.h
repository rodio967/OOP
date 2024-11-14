#ifndef OBSTACLE_H
#define OBSTACLE_H



#include "GameObject.h"

class Obstacle : public GameObject {
public:
    Obstacle();
    QPoint getPosition() const override;
    void setPosition(const QPoint& pos) override;

private:
    QPoint position;
};

#endif
