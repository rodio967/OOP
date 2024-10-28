#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "snake_obj.h"
#include "food.h"

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QPushButton>

class SnakeGame : public QWidget {
    Q_OBJECT

public:
    SnakeGame(QWidget *parent = nullptr);
    ~SnakeGame();
    void StartGame();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void moveSnake();
    void restartGame();

private:
    Snake_obj* snake;
    Food* food;
    QTimer *timer;
    int blockSize;
    int score;
    bool gameOver;
    bool isPause;
    bool isMoveBlocked;


    void checkCollision();
    void placeFood();
    void placeObstacles();
    void SetGameStatus();



    QVector<QPoint> obstacles;
    QPushButton *restartButton;

};

#endif
