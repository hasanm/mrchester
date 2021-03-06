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
#include "opencv2/opencv.hpp"

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
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:

private slots:
    void on_inputPushButton_pressed();
    void onStart();
    void onStop();
    void on_outputPushButton_pressed();
  void onZoomIn();
  void onZoomOut();


private:
  void setImage(const cv::Mat &src);
  void scaleImage();

  QPushButton *quitButton;
  QPushButton *startButton;
  QPushButton *stopButton;
  QPushButton *zoomInButton;
  QPushButton *zoomOutButton;
  QVBoxLayout *contentLayout;
  QImage image;
  QLabel *imageLabel;
  QScrollArea* scrollArea;
  double scaleFactor;
  cv::Mat mat; 
};

#endif // MAINWINDOW_H
