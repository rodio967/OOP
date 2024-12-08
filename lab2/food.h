#ifndef FOOD_H
#define FOOD_H


#include "GameObject.h"
#include "GameObjectVisitor.h"



class Food : public GameObject {
public:
    Food();
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
        return "Food";
    }

private:
    QPoint position;
    int index;
};

#endif // FOOD_H
