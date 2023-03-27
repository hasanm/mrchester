#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>


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


 private:
  QGraphicsView *view; 

  QGraphicsScene *scene;
  QGraphicsEllipseItem *ellipse;
  QGraphicsRectItem *rectangle;
  QGraphicsTextItem *text;
  QGraphicsPixmapItem *pixmap; 

  cv::Mat mat;

protected:
  void mousePressEvent(QMouseEvent* event) override;

}; 

#endif 
