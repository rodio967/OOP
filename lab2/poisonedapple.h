#ifndef POISONEDAPPLE_H
#define POISONEDAPPLE_H

#include "GameObject.h"
#include "GameObjectVisitor.h"



class PoisonedApple : public GameObject {
public:
    PoisonedApple();

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
        return "PoisonedApple";
    }

private:
    QPoint position;
    int index;
};

#endif // POISONEDAPPLE_H
