#ifndef SCREENAREA_H
#define SCREENAREA_H

#include <QtGui>
#include "ScreenView.h"

class ScreenArea : public QWidget
{
    Q_OBJECT

public:
    ScreenArea();

signals:
    void leaveArea();

private slots:
    void takeFullScreen();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    ScreenView* screenView;

    QPoint origin;
    QRubberBand* rubberBand;
    QAction* leaveAreaAction;
    QRect lastArea;

};

#endif // SCREENAREA_H
