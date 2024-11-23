#ifndef TELEPORT_H
#define TELEPORT_H

#include "GameObject.h"
#include "GameObjectVisitor.h"



class Teleport : public GameObject {
public:
    Teleport();
    QPoint getPosition() const override;
    void setPosition(const QPoint& pos) override;
    void accept(GameObjectVisitor& visitor) override {
        visitor.visit(*this);
    }

private:
    QPoint position;
};

#endif // TELEPORT_H