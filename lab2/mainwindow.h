#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QWidget>
#include <QPushButton>
#include "snakemodel.h"
#include "snakecontroller.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(SnakeModel *model, SnakeController *controller, QWidget *parent = nullptr);

public slots:
    void updateView();
    void restartGame();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    SnakeModel *model;
    SnakeController *controller;

    QPushButton *restartButton;

};
#endif
