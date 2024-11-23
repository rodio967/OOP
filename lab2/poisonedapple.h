#ifndef POISONEDAPPLE_H
#define POISONEDAPPLE_H

#include "GameObject.h"
#include "GameObjectVisitor.h"



class PoisonedApple : public GameObject {
public:
    PoisonedApple();

    QPoint getPosition() const override;
    void setPosition(const QPoint& pos) override;
    void accept(GameObjectVisitor& visitor) override {
        visitor.visit(*this);
    }

private:
    QPoint position;
};

#endif // POISONEDAPPLE_H
