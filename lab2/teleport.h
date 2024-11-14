#ifndef TELEPORT_H
#define TELEPORT_H

#include "GameObject.h"

class Teleport : public GameObject {
public:
    Teleport();
    QPoint getPosition() const override;
    void setPosition(const QPoint& pos) override;

private:
    QPoint position;
};

#endif
