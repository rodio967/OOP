#include "startmenu.h"
#include <QVBoxLayout>
#include <QLabel>

StartMenu::StartMenu(QWidget *parent) : QWidget(parent) {

    startButton = new QPushButton("Start", this);
    startButton->setGeometry(150, 150, 100, 50);

    startButton->setStyleSheet(
        "QPushButton {"
        "background-color: #4CAF50;"
        "border: none;"
        "color: white;"
        "padding: 15px 32px;"
        "text-align: center;"
        "font-size: 16px;"
        "border-radius: 12px;"
        "}"
        "QPushButton:hover {"
        "background-color: #45a049;"
        "}"
        );


    QLabel *titleLabel = new QLabel("Welcome to Snake Game!", this);
    titleLabel->setGeometry(50, 50, 320, 50);
    titleLabel->setStyleSheet(
        "QLabel {"
        "color: #333333;"
        "font-size: 24px;"
        "font-weight: bold;"
        "background-color: #2e8b57;"
        "border: 2px solid #2e8b57;"
        "padding: 10px;"
        "}"
        );

    setStyleSheet(
        "StartMenu {"
        "background-color: #f0f0f0;"
        "border: 2px solid #2e8b57;"
        "}"
        );


    connect(startButton, &QPushButton::clicked, this, &StartMenu::onStartClicked);
}

void StartMenu::onStartClicked() {
    emit startGame();
}
