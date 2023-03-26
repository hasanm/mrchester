#ifndef DRAWABLEIMAGE_H
#define DRAWABLEIMAGE_H

#include <QtWidgets>

class DrawableImage : public QWidget
{
  Q_OBJECT
  
 public:
  explicit DrawableImage(QWidget *parent =0);
  ~DrawableImage();


  public slots:
    void onClick();
    void onRelease();


 private:
    QLabel *imageLabel; 

};

#endif 
