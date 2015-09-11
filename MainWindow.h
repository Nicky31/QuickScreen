#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "ScreenArea.h"
#include "ScreenView.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void selectScreen();
    void leaveArea(QString lastScreen = "");

private:
    QLabel* lastScreenLb;
    ScreenArea* screenArea;
    QVBoxLayout* VLayout;
    QPushButton* selectScreenBt;
};
#endif // MAINWINDOW_H
