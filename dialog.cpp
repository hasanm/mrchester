#include "dialog.h"
#include <QStackedLayout>
#include <QGraphicsLinearLayout>
#include <QVBoxLayout>
#include <QtWidgets>

using namespace cv; 

Dialog::Dialog(QWidget *parent) :
  QDialog(parent)
{

  QVBoxLayout *layout = new QVBoxLayout(this);

  scene = new QGraphicsScene(this);


  QBrush greenBrush(Qt::green);
  QBrush blueBrush(Qt::blue);
  QPen outlinePen(Qt::black);
  outlinePen.setWidth(2);

  rectangle = scene->addRect(100, 0, 80, 100, outlinePen, blueBrush);
  ellipse = scene->addEllipse(0, -100, 300, 60, outlinePen, greenBrush);
  text = scene->addText("bogotobogo.com", QFont("Arial", 20));

  text->setFlag(QGraphicsItem::ItemIsMovable);


  view = new QGraphicsView();
  view->setScene(scene);
  layout->addWidget(view);

  this->setLayout(layout);

}


Dialog::~Dialog()
{
} 


void Dialog::setMatrix(Mat in)
{
  mat = in;
  Mat dest;
  cvtColor(mat,dest, COLOR_BGR2RGB);
  const QImage image((uchar *) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);

  QPixmap pix = QPixmap::fromImage(image);
  pixmap = scene->addPixmap(pix); 
} 


void Dialog::mousePressEvent(QMouseEvent* event)
{
  qDebug() << "Mouse Event"; 
} 
