#include "food.h"

Food::Food() {}

QPoint Food::getPosition() const
{
    return position;
}

void Food::setPosition(const QPoint &pos)
{
    position = pos;
}
