#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem> 

class Dialog : public QDialog
{
  Q_OBJECT


 public:
  explicit Dialog(QWidget *parent = 0);
  ~Dialog();

  QGraphicsView *view; 

  QGraphicsScene *scene;
  QGraphicsEllipseItem *ellipse;
  QGraphicsRectItem *rectangle;
  QGraphicsTextItem *text; 
}; 

#endif 
