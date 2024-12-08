#include "obstacle.h"

Obstacle::Obstacle() {}

QPoint Obstacle::getPosition() const
{
    return position;
}

void Obstacle::setPosition(const QPoint &pos)
{
    position = pos;
}
