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
    copyUrlBt = new QPushButton("Copier le lien");
    copyUrlBt->setVisible(false);

    HLayout->addWidget(exitBt);
    HLayout->addWidget(saveBt);
    HLayout->addWidget(upBt);
    HLayout->addWidget(copyUrlBt);

    VLayout->addWidget(screenPixMap);
    VLayout->addLayout(HLayout);
    setLayout(VLayout);

    QObject::connect(exitBt,SIGNAL(clicked()),this,SLOT(leaveScreenView()));
    QObject::connect(saveBt,SIGNAL(clicked()),this,SLOT(saveAs()));
    QObject::connect(upBt, SIGNAL(clicked()),this,SLOT(upload()));
    QObject::connect(copyUrlBt, SIGNAL(clicked()), this, SLOT(copyScreenUrl()));
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
    upBt->setVisible(true);
    upBt->setEnabled(true);
    copyUrlBt->setVisible(false);
}

void ScreenView::upload()
{
    upBt->setEnabled(false);

    QByteArray* pixmap = new QByteArray;
    QBuffer* buf = new QBuffer(pixmap);
    buf->open(QIODevice::WriteOnly);
    screenPixMap->pixmap()->save(buf, "PNG");
    buf->close();
    buf->open(QIODevice::ReadOnly);

    // Upload
    QNetworkRequest requete(QUrl("http://img.funky-emu.net/index.php?p=page/upload"));

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"upload\""));
    textPart.setBody(" ");

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/png"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"image[]\"; filename=\""+ generateFilename() +"\""));
    imagePart.setBodyDevice(buf);

    multiPart->append(imagePart);
    multiPart->append(textPart);

    QNetworkAccessManager *m = new QNetworkAccessManager;
    QNetworkReply *r = m->post(requete, multiPart);
    multiPart->setParent(r);

    connect(r, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(messageErreur(QNetworkReply::NetworkError)));
    connect(r, SIGNAL(finished()), this, SLOT(handleUploadReply()));
}

void ScreenView::handleUploadReply()
{
    QNetworkReply* r = qobject_cast<QNetworkReply *>(sender());

    QString reply(r->readAll());
    QRegExp urlRegexp("value=\"(http://.+\.png)\"");
    if(urlRegexp.indexIn(reply) != -1)
    {
        lastScreenUrl = urlRegexp.cap(1);
        upBt->setVisible(false);
        copyUrlBt->setVisible(true);
    }
    else
        QMessageBox::critical(this,"Erreur","Impossible d'extraire l'URL de l'image");
}

void ScreenView::copyScreenUrl()
{
    QClipboard* pressPaper = QApplication::clipboard();
    pressPaper->setText(lastScreenUrl);
    leaveScreenView();
}

void ScreenView::messageErreur(QNetworkReply::NetworkError)
{
    QNetworkReply *r = qobject_cast<QNetworkReply*>(sender());
    QMessageBox::critical(this, "Erreur", "Erreur lors de l'upload. Vérifiez votre connexion internet ou réessayez plus tard <br /><br /> Code de l'erreur : <br /><em>" + r->errorString() + "</em>");
    upBt->setEnabled(true);
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

QString ScreenView::generateFilename(QString ext) const
{
    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();
    return ("FS" + date.toString("dd-MM-yy ") + time.toString("h:mm:ss") + ext);
}
