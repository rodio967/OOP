#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <QPoint>

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual QPoint getPosition() const = 0;
    virtual void setPosition(const QPoint& position) = 0;
};




#endif
