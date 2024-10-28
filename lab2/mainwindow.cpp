#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QStackedWidget(parent) {
    startMenu = new StartMenu(this);
    snakeGame = new SnakeGame(this);

    addWidget(startMenu);
    addWidget(snakeGame);

    setCurrentWidget(startMenu);

    setStyleSheet("background-color: #f0f0f0;");

    connect(startMenu, &StartMenu::startGame, this, &MainWindow::showGame);
}

MainWindow::~MainWindow() {
    delete startMenu;
    delete snakeGame;
}

void MainWindow::showGame() {
    setCurrentWidget(snakeGame);
    snakeGame->setFocus();
    snakeGame->StartGame();
}
