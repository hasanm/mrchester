#include <QtWidgets>
#include "MyGraphicsView.h"

MyGraphicsView::MyGraphicsView()
{
    active = 0;
    x1 = y1 = 0;
    x2 = y2 = 100;
}

void MyGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "Double Clicked " << event->pos();
}

void MyGraphicsView::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "GV Mouse Pressed " << event->pos();
    active = 1;
}


void MyGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << "GV Mouse Released " << event->pos();
    active = 0;
}


void MyGraphicsView::mouseMoveEvent(QMouseEvent* event)
{
    qDebug() << "GV Moved " << event->pos();
    if (active ==1) {

    }
}
