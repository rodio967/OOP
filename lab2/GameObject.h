#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QPoint>
#include <string>



class GameObjectVisitor;

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual QPoint getPosition() const = 0;
    virtual void setPosition(const QPoint& position) = 0;
    virtual int getIndex() const = 0;
    virtual void setIndex(const int& index) = 0;

    virtual void accept(GameObjectVisitor& visitor) = 0;
    virtual std::string getType() const = 0;
};




#endif // GAMEOBJECT_H
