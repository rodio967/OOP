#ifndef OBSTACLE_H
#define OBSTACLE_H



#include "GameObject.h"
#include "GameObjectVisitor.h"




class Obstacle : public GameObject {
public:
    Obstacle();
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
        return "Obstacle";
    }

private:
    QPoint position;
    int index;
};

#endif // OBSTACLE_H
