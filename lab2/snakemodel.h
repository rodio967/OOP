#ifndef SNAKEMODEL_H
#define SNAKEMODEL_H

#include <QObject>
#include <QPoint>
#include <QTimer>
#include <QVector>
#include <QRandomGenerator>
#include <QPushButton>
#include <string>
#include <unordered_map>


#include "GameObject.h"
#include "GameObjectFactory.h"
#include "GameObjectVisitor.h"


struct Settings {
    int count;
    int maxPosition;
};

class SnakeModel : public QObject {
    Q_OBJECT
public:
    enum Direction { UP, DOWN, LEFT, RIGHT };

    explicit SnakeModel(QObject *parent = nullptr);

    void initGame();
    void StartGame();
    void changeDirection(Direction newDirection);

    void placeObjects(const std::unordered_map<std::string, Settings>& objectSettings);

    void checkCollision();
    bool isPositionOccupied(const QPoint& position);
    void placeFood();
    void placePoisoned_Apple();
    void placeTeleport();
    void growSnake();
    void decrease();
    void oneMove();
    void addScore();
    void checkBounds();
    void onUpDirection(Direction newDir);
    void onDownDirection(Direction newDir);
    void onLeftDirection(Direction newDir);
    void onRightDirection(Direction newDir);
    void SetGameStatus();
    void setSnakeHeadPosition(const QPoint& pos);
    std::vector<std::unique_ptr<GameObject>>& getGameObjects();

    QVector<QPoint> getSnake();

    QTimer* getTimer();

    bool isGameOver();
    void setGameOver();
    int getScore();


public slots:
    void moveSnake();


signals:
    void modelUpdated();

private:

    Direction dir;

    QTimer *timer;

    QVector<QPoint> snake;

    GameObjectFactory factory;

    std::unordered_map<std::string, Settings> objectSettings;


    std::vector<std::unique_ptr<GameObject>> gameObjects;


    int blockSize;
    int score;
    bool gameOver;
    bool isPause;
};

#endif // SNAKEMODEL_H
