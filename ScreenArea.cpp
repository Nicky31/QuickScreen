#include "ScreenArea.h"
#include <QtGui>

ScreenArea::ScreenArea()
{
    move(0,0); // Placement coin en haut à gauche
    setAttribute(Qt::WA_TranslucentBackground, true);

    setWindowFlags(Qt::FramelessWindowHint); // On enlève les bords
    showMaximized(); // On prend tout l'écran

    screenView = new ScreenView;
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    leaveAreaAction = new QAction("Annuler (Ctrl + F)",this);
    leaveAreaAction->setShortcut(QKeySequence("Ctrl+F"));

    // Menu contextuel
    addAction(leaveAreaAction);
    setContextMenuPolicy(Qt::ActionsContextMenu);

    QObject::connect(leaveAreaAction,SIGNAL(triggered()),this,SIGNAL(leaveArea()));
}

void ScreenArea::mousePressEvent(QMouseEvent *event)
{
    origin = event->pos();
    rubberBand->setGeometry(QRect(origin, QSize()));
    rubberBand->show();
}

void ScreenArea::mouseMoveEvent(QMouseEvent *event)
{
    rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
}

void ScreenArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(screenView->isVisible())
        return;

    QRect area = rubberBand->geometry();
    QPixmap screen = QPixmap::grabWindow(QApplication::desktop()->winId(),
                             area.x() + x() + 1,
                             area.y() + y() + 1,
                             area.width() - 2,
                             area.height() - 2);

    screenView->setScreenPixmap(screen);
}
