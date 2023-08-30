#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QtWidgets>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

private :
    int active = 0;
    int x1,y1, x2, y2;

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

public:
    MyGraphicsView();
};



#endif
