#include "snakemodel.h"
#include <QPainter>
#include <QRandomGenerator>

SnakeModel::SnakeModel(QObject *parent) : QObject(parent) {
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
    snake.push_back(QPoint(0, 0));

    food = GameObjectFactory::createObject(GameObjectFactory::FOOD);
    food->setPosition(QPoint(0, 0));

    poisoned_apple = GameObjectFactory::createObject(GameObjectFactory::POISONEDAPPLE);
    poisoned_apple->setPosition(QPoint(0, 0));

    teleport1 = GameObjectFactory::createObject(GameObjectFactory::TELEPORT);
    teleport1->setPosition(QPoint(0, 0));

    teleport2 = GameObjectFactory::createObject(GameObjectFactory::TELEPORT);
    teleport2->setPosition(QPoint(0, 0));



    obstacles.clear();
    placeObstacles();
    placeFood();
    placePoisoned_Apple();
    placeTeleport();
}

void SnakeModel::StartGame()
{
    timer->start(100);
}

void SnakeModel::changeDirection(Direction newDirection)
{
    if (newDirection == UP && dir != DOWN) {
        dir = UP;
    }else if (newDirection == DOWN && dir != UP) {
        dir = DOWN;
    }else if (newDirection == LEFT && dir != RIGHT) {
        dir = LEFT;
    }else if (newDirection == RIGHT && dir != LEFT) {
        dir = RIGHT;
    }
}

void SnakeModel::moveSnake()
{
    if (gameOver) {
        return;
    }

    QPoint newHead = snake.first();

    switch (dir) {
    case UP:    newHead.ry() -= 1; break;
    case DOWN:  newHead.ry() += 1; break;
    case LEFT:  newHead.rx() -= 1; break;
    case RIGHT: newHead.rx() += 1; break;
    }

    snake.push_front(newHead);
    snake.removeLast();

    int maxPosX = 20;
    int maxPosY = 20;

    if (snake[0].x() < 0) {
        snake[0].setX(maxPosX - 1);
    } else if (snake[0].x() >= maxPosX) {
        snake[0].setX(0);
    } else if (snake[0].y() < 0) {
        snake[0].setY(maxPosY - 1);
    } else if (snake[0].y() >= maxPosY) {
        snake[0].setY(0);
    }


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

    for (std::unique_ptr<GameObject> &obstacle : obstacles) {
        if (snake[0] == obstacle->getPosition()) {
            gameOver = true;
            return;
        }
    }

    if (snake[0] == food->getPosition()) {
        growSnake();
        placeFood();
        score += 10;
    }else if (snake[0] == teleport1->getPosition()) {
        snake[0] = teleport2->getPosition();
        placeTeleport();
    }else if (snake[0] == teleport2->getPosition()) {
        snake[0] = teleport1->getPosition();
        placeTeleport();
    }else if (snake[0] == poisoned_apple->getPosition()) {
        decrease();
        placePoisoned_Apple();
    }
}

void SnakeModel::placeFood() {
    int maxPos = 400 / blockSize;

    food = GameObjectFactory::createObject(GameObjectFactory::FOOD);

    bool onSnake = true;

    QPoint foodPosition;

    while(onSnake) {
        foodPosition.setX(QRandomGenerator::global()->bounded(maxPos));
        foodPosition.setY(QRandomGenerator::global()->bounded(maxPos));

        onSnake = false;
        for (const QPoint &segment : snake) {
            if (foodPosition == segment) {
                onSnake = true;
                break;
            }
        }
        if (onSnake == true) {
            continue;
        }

        for (std::unique_ptr<GameObject> &segment : obstacles){
            if (foodPosition == segment->getPosition()) {
                onSnake = true;
                break;
            }
        }

        if (foodPosition == teleport1->getPosition() || foodPosition == teleport2->getPosition() || foodPosition == poisoned_apple->getPosition()) {
            onSnake = true;
        }
    }

    food->setPosition(foodPosition);
}

void SnakeModel::placeObstacles()
{
    int maxPos = 400 / blockSize;
    int obstacleCount = 3;

    for (int i = 0; i < obstacleCount; i++) {
        bool onSnake_Food = true;
        QPoint obstaclePosition;

        auto obstacleObj = GameObjectFactory::createObject(GameObjectFactory::OBSTACLE);

        while (onSnake_Food) {
            obstaclePosition.setX(QRandomGenerator::global()->bounded(maxPos));
            obstaclePosition.setY(QRandomGenerator::global()->bounded(maxPos));

            onSnake_Food = false;

            for (const QPoint & segment : snake) {
                if (obstaclePosition == segment) {
                    onSnake_Food = true;
                    break;
                }
            }

        }

        obstacleObj->setPosition(obstaclePosition);

        obstacles.push_back(std::move(obstacleObj));
    }
}

void SnakeModel::placePoisoned_Apple()
{
    int maxPos = 400 / blockSize;
    poisoned_apple = GameObjectFactory::createObject(GameObjectFactory::POISONEDAPPLE);

    bool onSnake = true;
    QPoint applePosition;

    while(onSnake) {
        applePosition.setX(QRandomGenerator::global()->bounded(maxPos));
        applePosition.setY(QRandomGenerator::global()->bounded(maxPos));

        onSnake = false;

        for (const QPoint &segment : snake) {
            if (applePosition == segment) {
                onSnake = true;
                break;
            }
        }
        if (onSnake) {
            continue;
        }

        for (std::unique_ptr<GameObject> &segment : obstacles){
            if (applePosition == segment->getPosition()) {
                onSnake = true;
                break;
            }
        }

        if (applePosition == food->getPosition() || applePosition == teleport1->getPosition() || applePosition == teleport2->getPosition()) {
            onSnake = true;
        }

    }

    poisoned_apple->setPosition(applePosition);

}

void SnakeModel::placeTeleport()
{
    int maxPos = 400 / blockSize;

    teleport1 = GameObjectFactory::createObject(GameObjectFactory::TELEPORT);

    QPoint teleport1Position;

    bool onBody = true;

    while(onBody) {
        teleport1Position.setX(QRandomGenerator::global()->bounded(maxPos));
        teleport1Position.setY(QRandomGenerator::global()->bounded(maxPos));

        onBody = false;

        for (QPoint& segment : snake) {
            if (teleport1Position == segment) {
                onBody = true;
                break;
            }
        }

        if (onBody == true) {
            continue;
        }

        for (std::unique_ptr<GameObject> &segment : obstacles) {
            if (teleport1Position == segment->getPosition()) {
                onBody = true;
                break;
            }
        }

        if (teleport1Position == food->getPosition() || teleport1Position == poisoned_apple->getPosition()) {
            onBody = true;
        }
    }

    teleport1->setPosition(teleport1Position);

    teleport2 = GameObjectFactory::createObject(GameObjectFactory::TELEPORT);

    QPoint teleport2Position;

    onBody = true;

    while(onBody) {
        teleport2Position.setX(QRandomGenerator::global()->bounded(maxPos));
        teleport2Position.setY(QRandomGenerator::global()->bounded(maxPos));

        onBody = false;

        for (QPoint& segment : snake) {
            if (teleport2Position == segment) {
                onBody = true;
                break;
            }
        }

        if (onBody == true) {
            continue;
        }

        for (std::unique_ptr<GameObject> &segment : obstacles) {
            if (teleport2Position == segment->getPosition()) {
                onBody = true;
                break;
            }
        }

        if (teleport2Position == food->getPosition() || teleport2Position == poisoned_apple->getPosition()) {
            onBody = true;
        }
    }

    teleport2->setPosition(teleport2Position);



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

void SnakeModel::SetGameStatus()
{
    isPause = !isPause;
    if (isPause) {
        timer->stop();
    }else {
        timer->start(100);
    }
}

/*void SnakeModel::SetGameStatus()
{
    if (isPause) {
        timer->stop();
    }else {
        StartGame();
    }
}*/

QVector<QPoint> SnakeModel::getSnake()
{
    return snake;
}

const std::vector<std::unique_ptr<GameObject>>& SnakeModel::getObstacles() const
{
    return obstacles;
}

QPoint SnakeModel::getFood()
{
    return food->getPosition();
}

QPoint SnakeModel::getPoisoned_Apple()
{
    return poisoned_apple->getPosition();
}

QPoint SnakeModel::getTeleport1()
{
    return teleport1->getPosition();
}

QPoint SnakeModel::getTeleport2()
{
    return teleport2->getPosition();
}

QTimer *SnakeModel::getTimer()
{
    return timer;
}

bool SnakeModel::isGameOver()
{
    return gameOver;
}

int SnakeModel::getScore()
{
    return score;
}
