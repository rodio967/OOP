#include "mainwindow.h"
#include <QPainter>
#include "Food.h"
#include "PoisonedApple.h"
#include "obstacle.h"
#include "Teleport.h"


MainWindow::MainWindow(SnakeModel *model, SnakeController *controller, QWidget *parent)
    : QWidget(parent), model(model), controller(controller) {


    setFixedSize(400, 440);
    installEventFilter(controller);
    connect(model, &SnakeModel::modelUpdated, this, &MainWindow::updateView);


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
    connect(restartButton, &QPushButton::clicked, this, &MainWindow::restartGame);
}

void MainWindow::updateView()
{
    update();
}

void MainWindow::restartGame()
{
    model->initGame();
    restartButton->hide();
    model->getTimer()->start(100);
    update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.setBrush(Qt::lightGray);
    painter.drawRect(0, 0, 400, 400);
    if (model->isGameOver()) {
        model->getTimer()->stop();

        QRect gameOverRect(0, 100, width(), 50);
        QRect scoreRect(0, 150, width(), 50);
        painter.drawText(gameOverRect, Qt::AlignCenter, "Game Over");
        painter.drawText(scoreRect, Qt::AlignCenter, "Score: " + QString::number(model->getScore()));

        restartButton->setGeometry(width() / 2 - 50, 250, 100, 50);
        restartButton->show();
        return;
    }

    painter.setBrush(Qt::black);
    for (const QPoint &point : model->getSnake()) {
        painter.drawRect(point.x() * 20, point.y() * 20, 20, 20);
    }

    for (const std::unique_ptr<GameObject>& obj : model->getGameObjects()) {
        if (dynamic_cast<Food*>(obj.get())) {
            painter.setBrush(Qt::red);
        } else if (dynamic_cast<PoisonedApple*>(obj.get())) {
            painter.setBrush(QBrush(QColor(0, 255, 100)));
        } else if (dynamic_cast<Obstacle*>(obj.get())) {
            painter.setBrush(Qt::blue);
        } else if (dynamic_cast<Teleport*>(obj.get())) {
            painter.setBrush(Qt::yellow);
        }

        QPoint pos = obj->getPosition();
        painter.drawRect(pos.x() * 20, pos.y() * 20, 20, 20);
    }


    QRect scoreRect(0, 400, 400, 40);
    painter.setBrush(Qt::green);
    painter.drawRect(scoreRect);


    painter.setPen(Qt::black);
    painter.drawText(scoreRect, Qt::AlignCenter, "Score: " + QString::number(model->getScore()));
}
