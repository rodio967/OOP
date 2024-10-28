#include "snakegame.h"
#include <QPainter>
#include <QRandomGenerator>

SnakeGame::SnakeGame(QWidget *parent)
    : QWidget(parent), snake(new Snake_obj()), food(new Food()), blockSize(20), score(0), gameOver(false), isPause(false) {
    setFixedSize(400, 440);
    isMoveBlocked = false;


    obstacles.clear();
    placeObstacles();
    placeFood();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SnakeGame::moveSnake);

    restartButton = new QPushButton("Restart", this);

    restartButton->setStyleSheet(
        "QPushButton {"
        "background-color: #4CAF50;"
        "border: none;"
        "color: white;"
        "text-align: center;"
        "font-size: 16px;"
        "border-radius: 12px;"
        "}"
        "QPushButton:hover {"
        "background-color: #45a049;"
        "}"
        );

    restartButton->hide();

    connect(restartButton, &QPushButton::clicked, this, &SnakeGame::restartGame);
}

SnakeGame::~SnakeGame() {
    delete snake;
    delete food;
}

void SnakeGame::StartGame() {
    timer->start(100);
}


void SnakeGame::placeObstacles() {
    int maxPos = width() / blockSize;
    int obstacleCount = 3;

    for (int i = 0; i < obstacleCount; i++) {
        bool onSnake_Food = true;
        QPoint obstacle;

        while (onSnake_Food) {
            obstacle.setX(QRandomGenerator::global()->bounded(maxPos));
            obstacle.setY(QRandomGenerator::global()->bounded(maxPos));

            onSnake_Food = false;

            for (const QPoint & segment : snake->getBody()) {
                if (obstacle == segment) {
                    onSnake_Food = true;
                    break;
                }
            }

        }
        obstacles.push_back(obstacle);
    }
}

void SnakeGame::placeFood() {
    int maxPos = width() / blockSize;

    bool onSnake = true;
    while(onSnake) {
        food->new_Food(maxPos);

        onSnake = false;
        for (const QPoint &segment : snake->getBody()) {
            if (food->getPosition() == segment) {
                onSnake = true;
                break;
            }
        }
        if (onSnake == true) {
            continue;
        }

        for (const QPoint &segment : obstacles) {
            if (food->getPosition() == segment) {
                onSnake = true;
                break;
            }
        }
    }

}


void SnakeGame::SetGameStatus() {
    if (isPause) {
        timer->stop();
    }else {
        StartGame();
    }
}

void SnakeGame::moveSnake() {
    if (gameOver) {
        return;
    }

    snake->updatePosition();

    checkCollision();
    update();
}

void SnakeGame::restartGame() {
    delete snake;
    delete food;

    gameOver = false;
    score = 0;

    snake = new Snake_obj();
    food = new Food();

    obstacles.clear();
    placeObstacles();
    placeFood();

    restartButton->hide();
    StartGame();
    update();
}


void SnakeGame::checkCollision() {
    QVector<QPoint> new_snake = snake->getBody();


    for (int i = 1; i < new_snake.size(); ++i) {
        if (new_snake[0] == new_snake[i]) {
            gameOver = true;
            return;
        }
    }

    for (const QPoint &obstacle : obstacles) {
        if (new_snake[0] == obstacle) {
            gameOver = true;
            return;
        }
    }

    if (new_snake[0] == food->getPosition()) {
        snake->grow();
        placeFood();
        score += 10;
    }
}

void SnakeGame::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.setBrush(QBrush(Qt::lightGray));
    painter.drawRect(0, 0, 400, 400);

    if (gameOver) {
        timer->stop();

        QRect gameOverRect(0, 100, width(), 50);
        QRect scoreRect(0, 150, width(), 50);
        painter.drawText(gameOverRect, Qt::AlignCenter, "Game Over");
        painter.drawText(scoreRect, Qt::AlignCenter, "Score: " + QString::number(score));

        restartButton->setGeometry(width() / 2 - 50, 250, 100, 50);
        restartButton->show();
        return;
    }

    painter.setBrush(Qt::black);
    for (const QPoint &point : snake->getBody()) {
        painter.drawRect(point.x() * blockSize, point.y() * blockSize, blockSize, blockSize);
    }

    painter.setBrush(Qt::red);
    painter.drawRect(food->getPosition().x() * blockSize, food->getPosition().y() * blockSize, blockSize, blockSize);


    painter.setBrush(Qt::blue);
    for (const QPoint &obstacle : obstacles){
        painter.drawRect(obstacle.x() * blockSize, obstacle.y() * blockSize, blockSize, blockSize);
    }



    QRect scoreRect(0, 400, 400, 40);
    painter.setBrush(Qt::green);
    painter.drawRect(scoreRect);


    painter.setPen(Qt::black);
    painter.drawText(scoreRect, Qt::AlignCenter, "Score: " + QString::number(score));

    isMoveBlocked = false;
}

void SnakeGame::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        isPause = !isPause;
        SetGameStatus();
    }

    if (isMoveBlocked) {
        return;
    }

    if (event->key() == Qt::Key_W && snake->dir != Snake_obj::DOWN) {
        snake->dir = Snake_obj::UP;
    }

    if (event->key() == Qt::Key_S && snake->dir != Snake_obj::UP) {
        snake->dir = Snake_obj::DOWN;
    }

    if (event->key() == Qt::Key_A && snake->dir != Snake_obj::RIGHT) {
        snake->dir = Snake_obj::LEFT;
    }

    if (event->key() == Qt::Key_D && snake->dir != Snake_obj::LEFT) {
        snake->dir = Snake_obj::RIGHT;
    }

    isMoveBlocked = true;
}
