#include "food.h"

#include <QRandomGenerator>

Food::Food() {}

void Food::new_Food(int& maxPos) {
    position.setX(QRandomGenerator::global()->bounded(maxPos));
    position.setY(QRandomGenerator::global()->bounded(maxPos));
}

void Food::setPosition(const QPoint& newPos) {
    position = newPos;
}

QPoint Food::getPosition() {
    return position;
}
