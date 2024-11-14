#ifndef SNAKEMODEL_H
#define SNAKEMODEL_H

#include <QObject>
#include <QPoint>
#include <QTimer>
#include <QVector>
#include <QRandomGenerator>
#include <QPushButton>

#include "GameObjectFactory.h"

class SnakeModel : public QObject {
    Q_OBJECT
public:
    enum Direction { UP, DOWN, LEFT, RIGHT };

    explicit SnakeModel(QObject *parent = nullptr);

    void initGame();
    void StartGame();
    void changeDirection(Direction newDirection);

    void checkCollision();
    void placeFood();
    void placeObstacles();
    void placePoisoned_Apple();
    void placeTeleport();
    void growSnake();
    void decrease();
    void SetGameStatus();

    QVector<QPoint> getSnake();
    const std::vector<std::unique_ptr<GameObject>>& getObstacles() const;
    QPoint getFood();
    QPoint getPoisoned_Apple();
    QPoint getTeleport1();
    QPoint getTeleport2();
    QTimer* getTimer();

    bool isGameOver();
    int getScore();


public slots:
    void moveSnake();


signals:
    void modelUpdated();

private:
    Direction dir;

    QTimer *timer;

    QVector<QPoint> snake;
    std::vector<std::unique_ptr<GameObject>> obstacles;

    std::unique_ptr<GameObject> food;
    std::unique_ptr<GameObject> poisoned_apple;
    std::unique_ptr<GameObject> teleport1;
    std::unique_ptr<GameObject> teleport2;

    int blockSize;
    int score;
    bool gameOver;
    bool isPause;
};

#endif
