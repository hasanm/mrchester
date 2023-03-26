#include "graphicwindow.h"
#include <QGraphicsView>

#include <QGraphicsLinearLayout>
#include <QGraphicsGridLayout> 

GraphicWindow::GraphicWindow(QGraphicsWidget *parent) :
  QGraphicsWidget(parent, Qt::Window)
{

  QGraphicsLinearLayout *windowLayout = new QGraphicsLinearLayout(Qt::Vertical);
  QGraphicsLinearLayout *linear = new QGraphicsLinearLayout(windowLayout);

  

}

GraphicWindow::~GraphicWindow()
{
}
