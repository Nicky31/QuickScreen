#include "ScreenView.h"

ScreenView::ScreenView()
{
    setVisible(false);
    setWindowModality(Qt::WindowModal);

    screenPixMap = new QLabel;
    VLayout = new QVBoxLayout;
    HLayout = new QHBoxLayout;
    exitBt = new QPushButton("Refaire la capture");
    saveBt = new QPushButton("Enregistrer sous");
    upBt = new QPushButton("Mettre en ligne");
    SaveUpBt = new QPushButton("Enregistrer sous et mettre en ligne");

    HLayout->addWidget(exitBt);
    HLayout->addWidget(saveBt);
    //HLayout->addWidget(upBt);
    //HLayout->addWidget(SaveUpBt);

    VLayout->addWidget(screenPixMap);
    VLayout->addLayout(HLayout);
    setLayout(VLayout);

    QObject::connect(exitBt,SIGNAL(clicked()),this,SLOT(leaveScreenView()));
    QObject::connect(saveBt,SIGNAL(clicked()),this,SLOT(saveAs()));
}

void ScreenView::setScreenPixmap(QPixmap screen)
{
    /*
    QPainter painter(&screen);
    painter.setPen(Qt::blue);
    painter.setBrush(QBrush(QColor(255,255,255)));
    painter.setFont(QFont("Arial", 13));
    painter.drawText(screen.width() - 208,screen.height() - 13,"Funky ScreenShot");
    painter.end();*/

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

    QString fullPath = QFileDialog::getSaveFileName(this,"Enregistrer Sous",QString(),QString("PNG Files (*.png);;All Files (*.*)").toAscii().data());
    if(!fullPath.isEmpty())
    {
        if(fullPath.mid(fullPath.lastIndexOf("/") + 1).indexOf(".") == -1) // Aucun format renseigné
        {
            fullPath += ".png";
        }

        if(!screenPixMap->pixmap()->save(fullPath))
        {
            QMessageBox::critical(this,"Erreur","Une erreur s'est produite durant la sauvegarde de l'image.");
            return;
        }

        leaveScreenView();
    }
}

