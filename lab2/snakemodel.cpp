#include "snakemodel.h"
#include <QPainter>
#include <QRandomGenerator>
#include "CollisionVisitor.h"
#include "Food.h"
#include "PoisonedApple.h"

SnakeModel::SnakeModel(QObject *parent) : QObject(parent) {

    factory.Register("Food", CreateFood);
    factory.Register("Obstacle", CreateObstacle);
    factory.Register("Teleport", CreateTeleport);
    factory.Register("PoisonedApple", CreatePoisonedApple);
    objectSettings = {
        {"Obstacle", {3, 20}},
        {"Teleport", {4, 20}},
        {"Food", {1, 20}},
        {"PoisonedApple", {1, 20}}
    };

    initGame();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SnakeModel::moveSnake);
    timer->start(100);
}

void SnakeModel::initGame()
{
    dir = RIGHT;
    blockSize = 20;
    score = 0;
    gameOver = false;
    isPause = false;

    snake.clear();
    gameObjects.clear();
    snake.push_back(QPoint(0, 0));

    placeObjects(objectSettings);
}

void SnakeModel::StartGame()
{
    timer->start(100);
}

void SnakeModel::changeDirection(Direction newDirection)
{
    if (newDirection == UP) {
        onUpDirection(newDirection);
    }else if (newDirection == DOWN) {
        onDownDirection(newDirection);
    }else if (newDirection == LEFT) {
        onLeftDirection(newDirection);
    }else if (newDirection == RIGHT) {
        onRightDirection(newDirection);
    }
}

void SnakeModel::placeObjects(const std::unordered_map<std::string, Settings> &objectSettings)
{
    for (const auto& [type, settings] : objectSettings) {
        for (int i = 0; i < settings.count; ++i) {
            auto object = factory.CreateObject(type);
            QPoint position;

            do {
                position.setX(QRandomGenerator::global()->bounded(settings.maxPosition));
                position.setY(QRandomGenerator::global()->bounded(settings.maxPosition));
            } while (isPositionOccupied(position));

            object->setPosition(position);
            object->setIndex(i);
            gameObjects.push_back(std::move(object));
        }
    }
}

void SnakeModel::moveSnake()
{
    if (gameOver) {
        return;
    }

    oneMove();


    checkBounds();


    checkCollision();
    emit modelUpdated();
}


void SnakeModel::checkCollision() {
    for (int i = 1; i < snake.size(); ++i) {
        if (snake[0] == snake[i]) {
            gameOver = true;
            return;
        }
    }


    CollisionVisitor collisionVisitor(*this);
    for (auto& gameObject : gameObjects) {
        if (snake[0] == gameObject->getPosition()) {
            gameObject->accept(collisionVisitor);
            return;
        }
    }
}

bool SnakeModel::isPositionOccupied(const QPoint &position)
{
    for (const auto& snakeSegment : snake) {
        if (snakeSegment == position) {
            return true;
        }
    }

    for (const auto& gameObject : gameObjects) {
        if (position == gameObject->getPosition()) {
            return true;
        }
    }
    return false;
}

void SnakeModel::placeElem(const std::string& type, const int& index) {
    int maxPos = 400 / blockSize;

    for (auto& obj : gameObjects) {
        if (obj->getType() == type && obj->getIndex() == index) {
            QPoint foodPosition;
            do {
                foodPosition.setX(QRandomGenerator::global()->bounded(maxPos));
                foodPosition.setY(QRandomGenerator::global()->bounded(maxPos));
            } while (isPositionOccupied(foodPosition));

            obj->setPosition(foodPosition);

        }
    }
}

void SnakeModel::placeTeleport(const std::string& type, const int& index)
{
    int maxPos = 400 / blockSize;

    for (auto& obj : gameObjects) {
        if (obj->getType() == type && ((obj->getIndex() == index) || checkTeleports(index, obj->getIndex()))) {

            QPoint teleportPosition;
            do {
                teleportPosition.setX(QRandomGenerator::global()->bounded(maxPos));
                teleportPosition.setY(QRandomGenerator::global()->bounded(maxPos));
            } while (isPositionOccupied(teleportPosition));

            obj->setPosition(teleportPosition);
        }
    }
}





void SnakeModel::growSnake()
{
    snake.push_back(snake.back());
}

void SnakeModel::decrease()
{
    if (snake.size() > 1) {
        snake.removeLast();
    }
}

void SnakeModel::oneMove()
{
    QPoint newHead = snake.first();

    switch (dir) {
    case UP:    newHead.ry() -= 1; break;
    case DOWN:  newHead.ry() += 1; break;
    case LEFT:  newHead.rx() -= 1; break;
    case RIGHT: newHead.rx() += 1; break;
    }

    snake.push_front(newHead);
    snake.removeLast();
}

void SnakeModel::addScore()
{
    score += 10;
}

void SnakeModel::checkBounds()
{
    int MaxPos = 20;
    if (snake[0].x() < 0) {
        snake[0].setX(MaxPos - 1);
    } else if (snake[0].x() >= MaxPos) {
        snake[0].setX(0);
    } else if (snake[0].y() < 0) {
        snake[0].setY(MaxPos - 1);
    } else if (snake[0].y() >= MaxPos) {
        snake[0].setY(0);
    }
}

void SnakeModel::onUpDirection(Direction newDir)
{
    if (dir != DOWN) {
        dir = newDir;
    }
}

void SnakeModel::onDownDirection(Direction newDir)
{
    if (dir != UP) {
        dir = newDir;
    }
}

void SnakeModel::onLeftDirection(Direction newDir)
{
    if (dir != RIGHT) {
        dir = newDir;
    }
}

void SnakeModel::onRightDirection(Direction newDir)
{
    if (dir != LEFT) {
        dir = newDir;
    }
}


void SnakeModel::SetGameStatus()
{
    isPause = !isPause;
    if (isPause) {
        timer->stop();
    }else {
        timer->start(100);
    }
}

bool SnakeModel::checkTeleports(int ind1, int ind2)
{
    if ((((ind1 + ind2) % 4 == 1 ) && ((ind1 - ind2 == 1) || (ind2 - ind1 == 1)))) {
        return true;
    } else {
        return false;
    }
}

void SnakeModel::setSnakeHeadPosition(const QPoint &pos)
{
    snake[0] = pos;
}

std::vector<std::unique_ptr<GameObject> >& SnakeModel::getGameObjects()
{
    return gameObjects;
}


QVector<QPoint> SnakeModel::getSnake()
{
    return snake;
}



QTimer *SnakeModel::getTimer()
{
    return timer;
}

bool SnakeModel::isGameOver()
{
    return gameOver;
}

void SnakeModel::setGameOver()
{
    gameOver = true;
}

int SnakeModel::getScore()
{
    return score;
}
