#include <QtWidgets>
#include "MyGraphicsView.h"

void MyGraphicsView::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "Double Clicked " << event->pos();
}

void MyGraphicsView::mousePressEvent(QMouseEvent* event)
{
    qDebug() << "GV Mouse Pressed " << event->pos();
}


void MyGraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    qDebug() << "GV Mouse Released " << event->pos();
}
