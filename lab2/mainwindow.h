#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QStackedWidget>
#include <QWidget>
#include "startmenu.h"
#include "snakegame.h"

class MainWindow : public QStackedWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    StartMenu *startMenu;
    SnakeGame *snakeGame;

private slots:
    void showGame();
};

#endif
