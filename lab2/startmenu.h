#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QPushButton>

class StartMenu : public QWidget {
    Q_OBJECT

public:
    StartMenu(QWidget *parent = nullptr);

signals:
    void startGame();

private slots:
    void onStartClicked();

private:
    QPushButton *startButton;
};

#endif
