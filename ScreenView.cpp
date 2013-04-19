#include "ScreenView.h"

ScreenView::ScreenView()
{
    // Initialisation widgets
    screenPixMap = new QLabel;
    VLayout = new QVBoxLayout;
    HLayout = new QHBoxLayout;
    exitBt = new QPushButton("Refaire la capture");
    saveBt = new QPushButton("Enregistrer sous");
    upBt = new QPushButton("Mettre en ligne");
    SaveUpBt = new QPushButton("Enregistrer sous et mettre en ligne");

    // Placements
    HLayout->addWidget(exitBt);
    HLayout->addWidget(saveBt);
    //HLayout->addWidget(upBt);
    //HLayout->addWidget(SaveUpBt);

    VLayout->addWidget(screenPixMap);
    VLayout->addLayout(HLayout);

    setLayout(VLayout);

    setVisible(false);
    setWindowModality(Qt::WindowModal);

    // Connections
    QObject::connect(exitBt,SIGNAL(clicked()),this,SLOT(leaveScreenView()));
    QObject::connect(saveBt,SIGNAL(clicked()),this,SLOT(saveAs()));
}

void ScreenView::setScreenPixmap(QPixmap screen)
{
    screenPixMap->setPixmap(screen);
    setVisible(true);
}

void ScreenView::leaveScreenView()
{
    setVisible(false);
}

void ScreenView::saveAs()
{
    if(screenPixMap->pixmap()->isNull())
    {
        QMessageBox::critical(this,"Erreur","Aucun screenshot à sauvegarder.");
        return;
    }

    QString fullPath = QFileDialog::getSaveFileName(this,"Enregistrer Sous");
    if(!fullPath.isEmpty())
    {
        QString name = fullPath.mid(fullPath.lastIndexOf("/") + 1);
        if(!screenPixMap->pixmap()->save(fullPath))
        {
            QMessageBox::critical(this,"Erreur","Une erreur s'est produite durant la sauvegarde de l'image.");
        }
    }
}

