#include <QtWidgets>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include "mainwindow.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  sliderValue(50)
{
  QWidget *root = new QWidget(this);
  QWidget *top = new QWidget(this);
  QWidget *secondLine = new QWidget(this);
  QWidget *content = new QWidget(this);

  /* Top Layout */
  QHBoxLayout *topLayout = new QHBoxLayout(top);
  quitButton = new QPushButton(QString ("Quit"), this);
  quitButton->setToolTip(QString("A tooltip"));
  QFont font ("Courier");
  quitButton->setFont(font);
  QIcon icon("/home/p-hasan/work/qt/mrchester/my_icon.png");
  quitButton->setIcon(icon);
  connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
  topLayout->addWidget(quitButton);

  loadButton = new QPushButton(QString("Load Image"), this);
  loadButton->setIcon(QIcon::fromTheme("face-smile"));
  connect (loadButton, &QPushButton::clicked, this, &MainWindow::onLoad);
  topLayout->addWidget(loadButton);

  thresholdSlider = new QSlider(Qt::Horizontal, this);
  thresholdSlider->setMinimum(0);
  thresholdSlider->setMaximum(255);
  thresholdSlider->setValue(sliderValue);
  connect(thresholdSlider, &QSlider::valueChanged, this, &MainWindow::onSlider);
  topLayout->addWidget(thresholdSlider);

  sliderLabel = new QLabel(QString("Slider Value : "), this);
  topLayout->addWidget(sliderLabel);

  thresholdButton = new QPushButton(QString("Apply Threshold"), this);
  connect(thresholdButton, &QPushButton::clicked, this, &MainWindow::basicThreshold);
  topLayout->addWidget(thresholdButton);

  graphicButton = new QPushButton(QString("Open Graphics Scene"), this);
  connect (graphicButton, &QPushButton::clicked, this, &MainWindow::onGraphic);
  topLayout->addWidget(graphicButton);

  zoomInButton = new QPushButton(QString("Zoom In"), this);
  connect (zoomInButton, &QPushButton::clicked, this, &MainWindow::onZoomIn);
  topLayout->addWidget(zoomInButton);

  zoomOutButton = new QPushButton(QString("Zoom Out"), this);
  connect (zoomOutButton, &QPushButton::clicked, this, &MainWindow::onZoomOut);
  topLayout->addWidget(zoomOutButton);

  /* Second Layout */
  QHBoxLayout *secondLayout = new QHBoxLayout(secondLine);
  dimensionLabel = new QLabel(QString("No Image Loaded"), this);
  secondLayout->addWidget(dimensionLabel);



  /* Content Layout */
  contentLayout = new QVBoxLayout(content);
  scaleFactor = 1;
  imageLabel = new QLabel(this);
  imageLabel->setBackgroundRole(QPalette::Base);
  imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  imageLabel->setScaledContents(true);

  scrollArea = new QScrollArea;
  scrollArea->setBackgroundRole(QPalette::Dark);
  scrollArea->setWidget(imageLabel);


  contentLayout->addWidget(scrollArea);


  /* Root Layout */
  QVBoxLayout *rootLayout = new QVBoxLayout(root);
  rootLayout->addWidget(top);
  rootLayout->addWidget(secondLine);
  rootLayout->addWidget(content);
  setCentralWidget(root);

  exitAction = new QAction(tr("E&xit"));
  basicThresholdAction = new QAction(tr("&Basic Threshold"));
  connect (exitAction, &QAction::triggered,
           qApp, &QApplication::quit);

  connect (basicThresholdAction, &QAction::triggered,
           this, &MainWindow::basicThreshold);

  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(basicThresholdAction);
  fileMenu->addSeparator();
  fileMenu->addAction(exitAction);



  // Graphic Window
  graphicWindow = new GraphicWindow();


  // Dialog
  dialog = new Dialog(this);



  resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onLoad()
{

  Mat dest;
  // QDir::currentPath()
  QString fileName = QFileDialog::getOpenFileName(this, "Open Input Image", "/data/aoe_images", "Images (*.jpg *.png *.bmp)");
  if(QFile::exists(fileName))
    {
      mat = imread(fileName.toStdString().c_str(), IMREAD_COLOR);
      dimensionLabel->setText(QString("Image Dimension,  Rows: %1 x Cols: %2").arg(mat.rows).arg(mat.cols));

      cv::resize(mat,dest, Size(1920,1080), 0, 0, INTER_AREA);
      mat = dest;

      rectangle(mat, Point(0,0), Point(200, 300), Scalar(255,0,0), 2, LINE_8);
      setImage(mat);

      dialog->setMatrix(mat);

      const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
      statusBar()->showMessage(message);
    }
}


void MainWindow::scaleImage()
{
  Mat dest;

  int dcols = round(mat.cols  * scaleFactor);
  int drows = round(mat.rows  * scaleFactor);

  cv::resize(mat, dest, Size(dcols, drows), 0, 0, (scaleFactor < 1) ? INTER_AREA : INTER_LINEAR);
  qDebug() << scaleFactor << ": " << dcols << "," << drows;
  setImage(dest);
}

void MainWindow::setImage(const Mat &src)
{

  Mat dest;
  cvtColor(src, dest,COLOR_BGR2RGB);
  const QImage newImage((uchar*) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
  // const QImage newImage(dest.data, dest.cols, dest.rows, QImage::Format_RGB888);

  image = newImage;
  QPixmap pix;
  pix = QPixmap::fromImage(image);
  imageLabel->setPixmap(pix);
  imageLabel->adjustSize();

  QRect r1(100, 200, 11, 16);
}



void MainWindow::setImageGray(const Mat &src)
{

  Mat dest;
  cvtColor(src, dest,COLOR_BGR2RGB);
  const QImage newImage((uchar*) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
  // const QImage newImage(dest.data, dest.cols, dest.rows, QImage::Format_RGB888);

  image = newImage;
  QPixmap pix;
  pix = QPixmap::fromImage(image);
  imageLabel->setPixmap(pix);
  imageLabel->adjustSize();

  QRect r1(100, 200, 11, 16);
}

void MainWindow::onGraphic()
{
  // graphicWindow->show();

  dialog->show();
}


void MainWindow::onZoomIn()
{
  scaleFactor += 0.05;
  scaleImage();
}


void MainWindow::onZoomOut()
{
  scaleFactor -= 0.05;
  scaleImage();
}

void MainWindow::on_inputPushButton_pressed()
{
  //
    QString fileName = QFileDialog::getOpenFileName(this, "Open Input Image", "/data/aoe_images", "Images (*.jpg *.png *.bmp)");
    if(QFile::exists(fileName))
    {

    }
}

void MainWindow::on_outputPushButton_pressed()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Select Output Image", QDir::currentPath(), "*.jpg;;*.png;;*.bmp");
    if(!fileName.isEmpty())
    {
    }
}

void MainWindow::basicThreshold()
{

  Mat gray, dst;
  int threshold_value = sliderValue;
  int threshold_type = 3;
  int const max_value = 255;
  int const max_type = 4;
  int const max_binary_value = 255;

  cvtColor(mat, gray, COLOR_BGR2GRAY);
  threshold(gray, dst, threshold_value, max_binary_value, threshold_type);

  setImageGray(dst);
}


void MainWindow::onSlider(int value) {
  sliderLabel->setText(QString("Slider Value: %1").arg(value));
  sliderValue = value;
}





void MainWindow::defaultLoad()
{

  Mat dest;
  Mat gray;

  Mat tmp, tmp1;
  // QDir::currentPath()
  QString fileName = QString("/data/test_images/01.png");
  if(QFile::exists(fileName))
    {
      mat = imread(fileName.toStdString().c_str(), IMREAD_COLOR);
      dimensionLabel->setText(QString("Image Dimension,  Rows: %1 x Cols: %2").arg(mat.rows).arg(mat.cols));

      // cv::resize(mat,dest, Size(1920,1080), 0, 0, INTER_AREA);
      // mat = dest;

      Scalar color[3] = {Scalar(255,0,0), Scalar(0,255,0), Scalar(0,0,255)};

      for (int i = 0; i < 256; i++) {
          int x1, y1, x2, y2;
          x1 = i * 10;
          y1 = 0;

          x2 = x1;
          y2 = 600;


          if (i%10 == 0) {
              line(mat, Point(x1,y1), Point(x2,y2), Scalar(255,0,0), 1, LINE_8);
          } else if (i%5 == 0) {
              line(mat, Point(x1,y1), Point(x2,y2), Scalar(100,100,0), 1, LINE_8);
          } else {
              line(mat, Point(x1,y1), Point(x2,y2), Scalar(0,0,0), 1, LINE_8);
          }


      }

      rectangle(mat, Point(65,0) , Point(145,65), color[0], 2, LINE_8);
      rectangle(mat, Point(200,0), Point(280,65), color[0], 2, LINE_8);
      rectangle(mat, Point(330,0), Point(410,65), color[0], 2, LINE_8);
      rectangle(mat, Point(465,0), Point(545,65), color[0], 2, LINE_8);
      rectangle(mat, Point(600,0), Point(700,65), color[0], 2, LINE_8);

      // for (int i = 0; i < 5; i++) {
      //     int x1 = i * 130 + 10;
      //     int y1 = 0;
      //     int x2 = x1 + 130 + (i == 4) ? 20 : 0;
      //     int y2 = 65;
      //     rectangle(mat, Point(x1,y1), Point(x2,y2), color[i%3], 2, LINE_8);
      //
      //     int x3 = x1 + 40;
      //     int y3 = y1 + 10;
      //     // rectangle(mat, Point(x3,y3), Point(x2,y2), color[(i+1)%3], 2, LINE_8);
      //
      //
      //     int x4 = x1 + 10;
      //     int y4 = y1 + 28;
      //     int x5 = x4 + 28;
      //     int y5 = y4 + 22;
      //     // rectangle(mat, Point(x4,y4), Point(x5,y5), color[(i+2)%3], 2, LINE_8);
      //
      //     Mat clipped (mat, Rect(x1,y1,x2, y2));
      //     if (i == 0) {
      //         cvtColor(clipped, gray, COLOR_BGR2GRAY);
      //         threshold(gray, tmp, 150, 255, cv::THRESH_BINARY_INV);
      //         // cv::resize(tmp,tmp1, Size(1920,1080), 0, 0, INTER_AREA);
      //         imwrite("out.png", tmp);
      //     }
      // // rectangle(mat, Point(x,0), Point(x + 110, 50), Scalar(255,0,0), 2, LINE_8);
      // }


      setImage(mat);

      dialog->setMatrix(mat);

      const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
      statusBar()->showMessage(message);
    }
}
