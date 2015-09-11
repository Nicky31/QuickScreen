#ifndef SCREENVIEW_H
#define SCREENVIEW_H

#include <QtGui>
#include <QtNetwork>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

class ScreenView : public QWidget
{
    Q_OBJECT

public:
    ScreenView();
    void setScreenPixmap(QPixmap screen);
    QString generateFilename(QString ext = ".png") const;

signals:
    void screenSaved(QString);

private slots:
    void leaveScreenView();
    void saveAs();
    void upload();
    void messageErreur(QNetworkReply::NetworkError);
    void handleUploadReply();
    void copyScreenUrl();

private:
    QLabel* screenPixMap;
    QVBoxLayout* VLayout;
    QHBoxLayout* HLayout;
    QPushButton* exitBt;
    QPushButton* saveBt;
    QPushButton* upBt;
    QPushButton* copyUrlBt;

    QString lastScreenUrl;

};

#endif // SCREENVIEW_H
