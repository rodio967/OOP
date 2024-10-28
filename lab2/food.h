#ifndef FOOD_H
#define FOOD_H

#include <QWidget>

class Food {
public:
    Food();

    void new_Food(int& maxPos);
    void setPosition(const QPoint& newPos);
    QPoint getPosition();

private:
    QPoint position;
};

#endif
