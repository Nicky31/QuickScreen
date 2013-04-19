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
    void leaveArea();

private:
    ScreenArea* screenArea;
    ScreenView* screenView;

    QVBoxLayout* VLayout;
    QPushButton* selectScreenBt;
    QLabel* screenUrlLb;

};
#endif // MAINWINDOW_H
