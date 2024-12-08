#ifndef TELEPORT_H
#define TELEPORT_H

#include "GameObject.h"
#include "GameObjectVisitor.h"



class Teleport : public GameObject {
public:
    Teleport();
    QPoint getPosition() const override;
    void setPosition(const QPoint& pos) override;
    int getIndex() const override {
        return index;
    }
    void setIndex(const int& ind) override {
        index = ind;
    }

    void accept(GameObjectVisitor& visitor) override {
        visitor.visit(*this);
    }

    std::string getType() const override {
        return "Teleport";
    }

private:
    QPoint position;
    int index;
};

#endif // TELEPORT_H
