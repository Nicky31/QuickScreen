#include <QtGui>
#include "MainWindow.h"

MainWindow::MainWindow()
{
    setWindowTitle("Funky ScreenShot");

    QDesktopWidget* bureau = QApplication::desktop();
    int x = (bureau->screenGeometry(bureau->primaryScreen()).width()/2) - (width()/2);
    int y = (bureau->screenGeometry(bureau->primaryScreen()).height()/2) - (height()/2);
    move(x,y);

    // Initialisation des Widgets
    VLayout = new QVBoxLayout;
    selectScreenBt = new QPushButton("Selectionner un espace de screen");
    screenUrlLb = new QLabel;

    screenArea = new ScreenArea; // Espace de sélection
    screenArea->setVisible(false);
    screenView = new ScreenView; // Widget d'affichage du screen

    // Placement
    VLayout->addWidget(selectScreenBt);
    VLayout->addWidget(screenUrlLb);
    setLayout(VLayout);

    // Connections
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
