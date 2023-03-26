#ifndef DRAWABLEIMAGE_H
#define DRAWABLEIMAGE_H

class DrawableImage : public QWidget
{
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
