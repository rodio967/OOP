#include "snakecontroller.h"



SnakeController::SnakeController(SnakeModel *model, QObject *parent)
    : QObject(parent), model(model) {}

bool SnakeController::eventFilter(QObject *obj, QEvent *event) {

    if (event->type() == QEvent::KeyPress) {
        auto *keyEvent = static_cast<QKeyEvent *>(event);
        keyPressEvent(keyEvent);
        return true;
    }
}

void SnakeController::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W: model->changeDirection(SnakeModel::UP); break;
    case Qt::Key_S: model->changeDirection(SnakeModel::DOWN); break;
    case Qt::Key_A: model->changeDirection(SnakeModel::LEFT); break;
    case Qt::Key_D: model->changeDirection(SnakeModel::RIGHT); break;
    case Qt::Key_Space:
        model->SetGameStatus();
    }
}


