#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QCloseEvent>
#include <QMessageBox>
#include <QSettings>
#include <QImage>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QColor>

#include <opencv2/opencv.hpp>
#include "graphicwindow.h"
#include "MyGraphicsView.h"

QT_BEGIN_NAMESPACE
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QComboBox;
class QVBoxLayout;
class QIcon;
class QTableWidget;
class QGridLayout;
class QScrollArea;
class QScrollBar;
class QSlider;
QT_END_NAMESPACE

class MyGraphicsView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void defaultLoad();
    void onMousePressed(QMouseEvent* event);
    void onMouseReleased(QMouseEvent* event);
    void onMouseMoved(QMouseEvent* event);

protected:

private slots:
    void on_inputPushButton_pressed();
    void onLoad();
    void onGraphic();
    void on_outputPushButton_pressed();
  void onZoomIn();
  void onZoomOut();

  void basicThreshold();
  void onSlider(int value);


private:
  void setImage(const cv::Mat &src);
  void setImageGray(const cv::Mat &src);
  void scaleImage();

  QPushButton *quitButton;
  QPushButton *loadButton;
  QPushButton *graphicButton;
  QPushButton *zoomInButton;
  QPushButton *zoomOutButton;
  QPushButton *thresholdButton;
  QSlider *thresholdSlider;

  QLabel *sliderLabel;
  QLabel *dimensionLabel;

  QVBoxLayout *contentLayout;
  QImage image;
  QLabel *imageLabel;
  QScrollArea* scrollArea;
  double scaleFactor;
  cv::Mat mat;

  // Menu Variables
  QMenu *fileMenu;
  QAction *exitAction;
  QAction *basicThresholdAction;

  GraphicWindow *graphicWindow;


  int sliderValue;

    MyGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmap;
    QGraphicsRectItem *rectangle;
    QPointF top_p;
    QPointF bottom_p;
    int active;
    // QBrush greenBrush(Qt::green);
    // QBrush redBrush(Qt::red);
    QBrush blueBrush;
    QPen outlinePen;

};

#endif // MAINWINDOW_H
