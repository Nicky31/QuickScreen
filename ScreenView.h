#ifndef SCREENVIEW_H
#define SCREENVIEW_H

#include <QtGui>

class ScreenView : public QWidget
{
    Q_OBJECT

public:
    ScreenView();
    void setScreenPixmap(QPixmap screen);

private slots:
    void leaveScreenView();
    void saveAs();

private:
    QLabel* screenPixMap;
    QVBoxLayout* VLayout;
    QHBoxLayout* HLayout;
    QPushButton* exitBt;
    QPushButton* saveBt;
    QPushButton* upBt;
    QPushButton* SaveUpBt;
};

#endif // SCREENVIEW_H
