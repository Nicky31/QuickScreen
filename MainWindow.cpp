#include <QtGui>
#include "MainWindow.h"

MainWindow::MainWindow()
{
    setWindowTitle("Funky ScreenShot");

    QDesktopWidget* bureau = QApplication::desktop();
    int x = (bureau->screenGeometry(bureau->primaryScreen()).width()/2) - (width()/2);
    int y = (bureau->screenGeometry(bureau->primaryScreen()).height()/2) - (height()/2);
    move(x,y);

    VLayout = new QVBoxLayout;
    selectScreenBt = new QPushButton("Selectionner un espace de screen");
    lastScreenLb = new QLabel;

    screenArea = new ScreenArea; // Espace de sélection
    screenArea->setVisible(false);

    VLayout->addWidget(selectScreenBt);
    VLayout->addWidget(lastScreenLb);
    setLayout(VLayout);

    QObject::connect(selectScreenBt,SIGNAL(clicked()),this,SLOT(selectScreen())); // Sélectionner un espace de screen
    QObject::connect(screenArea,SIGNAL(leaveArea()),this,SLOT(leaveArea())); // On quitte l'espace de screen
    QObject::connect(screenArea, SIGNAL(screenSaved(QString)), this, SLOT(leaveArea(QString)));
}

void MainWindow::selectScreen()
{
    setVisible(false);
    screenArea->setVisible(true);
}

void MainWindow::leaveArea(QString lastScreen)
{
    setVisible(true);
    screenArea->setVisible(false);

    if(lastScreen != "")
        lastScreenLb->setText("Dernier screen : " + lastScreen);
}
