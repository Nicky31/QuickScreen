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

    screenArea = new ScreenArea; // Espace de sélection
    screenArea->setVisible(false);

    VLayout->addWidget(selectScreenBt);
    setLayout(VLayout);

    QObject::connect(selectScreenBt,SIGNAL(clicked()),this,SLOT(selectScreen())); // Sélectionner un espace de screen
    QObject::connect(screenArea,SIGNAL(leaveArea()),this,SLOT(leaveArea())); // On quitte l'espace de screen
}

void MainWindow::selectScreen()
{
    setVisible(false);
    screenArea->setVisible(true);
}

void MainWindow::leaveArea()
{
    setVisible(true);
    screenArea->setVisible(false);
}
