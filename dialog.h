#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QtWidgets>


#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std; 

class Dialog : public QDialog
{
  Q_OBJECT


 public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void setMatrix(cv::Mat in);
    void onMousePressed(QMouseEvent* event);
    void onMouseReleased(QMouseEvent* event);
    void onMouseMoved(QMouseEvent* event);    

 private:
    QGraphicsView *view; 

    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsTextItem *text;
    QGraphicsPixmapItem *pixmap; 

    cv::Mat mat;

    QPointF top;
    QPointF bottom;
    int active;
    // QBrush greenBrush(Qt::green);
    QBrush blueBrush;
    QPen outlinePen;


}; 

#endif 
