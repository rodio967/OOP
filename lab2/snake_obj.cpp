#include "snake_obj.h"

Snake_obj::Snake_obj() {
    body.push_back(QPoint(0, 0));
    dir = RIGHT;
}

QPoint Snake_obj::getPosition() {
    return body.first();
}

void Snake_obj::setPosition(const QPoint& newPos) {
    body.first() = newPos;
}

void Snake_obj::updatePosition()
{
    QPoint newHead = body.first();

    switch (dir) {
    case UP:    newHead.ry() -= 1; break;
    case DOWN:  newHead.ry() += 1; break;
    case LEFT:  newHead.rx() -= 1; break;
    case RIGHT: newHead.rx() += 1; break;
    }

    body.push_front(newHead);
    body.removeLast();

    int maxPosX = 20;
    int maxPosY = 20;

    if (body[0].x() < 0) {
        body[0].setX(maxPosX - 1);
    } else if (body[0].x() >= maxPosX) {
        body[0].setX(0);
    } else if (body[0].y() < 0) {
        body[0].setY(maxPosY - 1);
    } else if (body[0].y() >= maxPosY) {
        body[0].setY(0);
    }
}

void Snake_obj::grow() {
    body.push_back(body.back());
}

QVector<QPoint> Snake_obj::getBody() {
    return body;
}
