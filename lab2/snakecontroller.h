#ifndef SNAKECONTROLLER_H
#define SNAKECONTROLLER_H

#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include "snakemodel.h"

class SnakeController : public QObject {

public:
    explicit SnakeController(SnakeModel *model, QObject *parent = nullptr);
    bool eventFilter(QObject *obj, QEvent *event) override;

    void keyPressEvent(QKeyEvent *event);

private slots:
    void updateGame();

private:
    SnakeModel *model;

};

#endif
