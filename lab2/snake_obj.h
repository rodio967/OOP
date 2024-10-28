#ifndef SNAKE_OBJ_H
#define SNAKE_OBJ_H

#include <QWidget>

class Snake_obj
{
public:
    Snake_obj();

    QPoint getPosition();
    void setPosition(const QPoint& newPos);
    void updatePosition();

    void grow();
    QVector<QPoint> getBody();

    enum Direction { UP, DOWN, LEFT, RIGHT };
    Direction dir;

private:
    QVector<QPoint> body;
};

#endif
