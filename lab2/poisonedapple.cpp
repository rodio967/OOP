#include "poisonedapple.h"

PoisonedApple::PoisonedApple() {}

QPoint PoisonedApple::getPosition() const
{
    return position;
}

void PoisonedApple::setPosition(const QPoint &pos)
{
    position = pos;
}
