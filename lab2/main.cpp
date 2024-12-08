#include <QApplication>
#include "snakemodel.h"
#include "snakecontroller.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SnakeModel model;
    SnakeController controller(&model);

    MainWindow view(&model, &controller);
    view.show();

    return a.exec();
}
