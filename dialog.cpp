#include "dialog.h"
#include <QStackedLayout>
#include <QGraphicsLinearLayout>
#include <QVBoxLayout>
#include <QtWidgets>
#include "MyGraphicsView.h"

using namespace cv;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    outlinePen(Qt::black),
    blueBrush(Qt::blue)
{

  QVBoxLayout *layout = new QVBoxLayout(this);

  scene = new QGraphicsScene(this);
  // 

  // rectangle = scene->addRect(100, 0, 80, 100, outlinePen, blueBrush);
  // ellipse = scene->addEllipse(0, -100, 300, 60, outlinePen, greenBrush);
  // text = scene->addText("bogotobogo.com", QFont("Arial", 20));

  // text->setFlag(QGraphicsItem::ItemIsMovable);


  view = new MyGraphicsView(this);
  view->setMouseTracking(true);
  view->setScene(scene);
  layout->addWidget(view);


  QString fileName = QString("/data/homeworks/test_data/1.JPG");
  Mat mat;
  if (QFile::exists(fileName)) {
      mat = imread(fileName.toStdString().c_str(), IMREAD_COLOR);
      this->setMatrix(mat);
  }

  this->setLayout(layout);

  active = 0; 
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


void Dialog::onMousePressed(QMouseEvent* event)
{
    qDebug() << "D Mouse Pressed " << event->pos();
    active = 1;
    top = event->pos();
    bottom = top + QPoint (100, 100);
    outlinePen.setWidth(2);
    rectangle = new QGraphicsRectItem(QRectF(top, bottom));
    scene->addItem(rectangle);
}



