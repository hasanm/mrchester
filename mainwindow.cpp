#include <QtWidgets>
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include "mainwindow.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv; 



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
  QWidget *root = new QWidget(this);
  QWidget *top = new QWidget(this);
  QWidget *content = new QWidget(this);

  /* Top Layout */
  QHBoxLayout *topLayout = new QHBoxLayout(top);
  quitButton = new QPushButton(QString ("Quit"), this);
  connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
  topLayout->addWidget(quitButton);

  startButton = new QPushButton(QString("Start CV"), this);
  connect (startButton, &QPushButton::clicked, this, &MainWindow::onStart);
  topLayout->addWidget(startButton);

  stopButton = new QPushButton(QString("Stop CV"), this);
  connect (stopButton, &QPushButton::clicked, this, &MainWindow::onStop);
  topLayout->addWidget(stopButton);

  zoomInButton = new QPushButton(QString("Zoom In"), this);
  connect (zoomInButton, &QPushButton::clicked, this, &MainWindow::onZoomIn);
  topLayout->addWidget(zoomInButton);

  zoomOutButton = new QPushButton(QString("Zoom Out"), this);
  connect (zoomOutButton, &QPushButton::clicked, this, &MainWindow::onZoomOut);
  topLayout->addWidget(zoomOutButton);

  /* Content Layout */
  contentLayout = new QVBoxLayout(content);
  scaleFactor = 1;  
  imageLabel = new QLabel();
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
  rootLayout->addWidget(content);
  setCentralWidget(root);

  resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onStart()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Open Input Image", QDir::currentPath(), "Images (*.jpg *.png *.bmp)");
    if(QFile::exists(fileName))
    {
      mat = imread(fileName.toStdString().c_str(), IMREAD_COLOR);
      setImage(mat);

      const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
      statusBar()->showMessage(message);
    }
}

void MainWindow::setImage(const Mat &src)
{

  Mat dest;
  cvtColor(src, dest,COLOR_BGR2RGB);
  const QImage newImage(dest.data, dest.cols, dest.rows, QImage::Format_RGB888);

  image = newImage;
  imageLabel->setPixmap(QPixmap::fromImage(image));
  imageLabel->adjustSize();
}

void MainWindow::onStop()
{
}


void MainWindow::onZoomIn()
{
  scaleFactor *= 1.25;
  scaleImage();
}


void MainWindow::onZoomOut()
{
  scaleFactor *= 0.75;
  scaleImage();
}


void MainWindow::scaleImage()
{
  // image = image.scaled(image.size() * factor, Qt::KeepAspectRatio);
  // imageLabel->setPixmap(QPixmap::fromImage(image));
  Mat dest;
  cv::resize(mat, dest, Size(), scaleFactor, scaleFactor, (scaleFactor < 1) ? INTER_AREA : INTER_LINEAR);
  qDebug() << scaleFactor; 
  setImage(dest);
}

void MainWindow::on_inputPushButton_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Input Image", QDir::currentPath(), "Images (*.jpg *.png *.bmp)");
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
