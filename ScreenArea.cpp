#include "ScreenArea.h"
#include <QtGui>

ScreenArea::ScreenArea()
{
    move(0,0); // Placement coin en haut à gauche
    setWindowOpacity(0.5); // Transparence
    setWindowFlags(Qt::FramelessWindowHint); // On enlève les bords
    showMaximized(); // On prend tout l'écran

    // Initialisation Widgets
    screenView = new ScreenView;
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    rubberBand->setWindowOpacity(0);
    leaveAreaAction = new QAction("Annuler",this);
    fullScreenAction = new QAction("Capture complète",this);

    // Menu contextuel
    addAction(leaveAreaAction);
    addAction(fullScreenAction);
    setContextMenuPolicy(Qt::ActionsContextMenu);

    // Connections
    QObject::connect(leaveAreaAction,SIGNAL(triggered()),this,SIGNAL(leaveArea()));
    QObject::connect(fullScreenAction,SIGNAL(triggered()),this,SLOT(takeFullScreen()));
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
    {
        return;
    }

    QRect area = rubberBand->geometry();
    QPixmap screen = QPixmap::grabWindow(QApplication::desktop()->winId(),
                             area.x() + x() + 1,
                             area.y() + y() + 1,
                             area.width() - 2,
                             area.height() - 2);
    screenView->setScreenPixmap(screen);
}

void ScreenArea::takeFullScreen()
{
    QPixmap originalPixmap = QPixmap::grabWindow(winId());
    screenView->setScreenPixmap(originalPixmap);
}
