#include "teleport.h"

Teleport::Teleport() {}

QPoint Teleport::getPosition() const
{
    return position;
}

void Teleport::setPosition(const QPoint &pos)
{
    position = pos;
}
