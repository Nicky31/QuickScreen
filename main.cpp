#include <QtGui>
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow Window;
    Window.show();

    return app.exec();
}

