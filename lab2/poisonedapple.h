#ifndef POISONEDAPPLE_H
#define POISONEDAPPLE_H

#include "GameObject.h"

class PoisonedApple : public GameObject {
public:
    PoisonedApple();

    QPoint getPosition() const override;
    void setPosition(const QPoint& pos) override;

private:
    QPoint position;
};

#endif
