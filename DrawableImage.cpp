#include <QtWidgets>
#include "DrawableImage.h"


DrawableImage::DrawableImage(QWidget* parent)
  :QWidget(parent)
{
  imageLabel = new QLabel(this);
  imageLabel->setBackgroundRole(QPalette::Base);
  imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabel->setScaledContents(true);
  
}

DrawableImage::~DrawableImage()
{
} 


void DrawableImage::onClick()
{
}

void DrawableImage::onRelease()
{
}
