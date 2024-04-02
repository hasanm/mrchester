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
  sliderValue(50),
  pixmap (nullptr),
  rectangle(nullptr)
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
  scene = new QGraphicsScene(this);
  view  = new MyGraphicsView(this);
  view->setMouseTracking(true);
  view->setScene(scene);
  view->scale(.5,.5);

  contentLayout->addWidget(view);


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
  // graphicWindow = new GraphicWindow();


  resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onLoad()
{

  // QDir::currentPath()
  QString fileName = QFileDialog::getOpenFileName(this, "Open Input Image", "/data/aoe_images", "Images (*.jpg *.png *.bmp)");
  if(QFile::exists(fileName))
    {
      mat = imread(fileName.toStdString().c_str(), IMREAD_COLOR);
      dimensionLabel->setText(QString("Image Dimension,  Rows: %1 x Cols: %2").arg(mat.rows).arg(mat.cols));

      setImage(mat);


      const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
      statusBar()->showMessage(message);
    }
}


void MainWindow::scaleImage()
{

}

void MainWindow::setImage(const Mat &src)
{

  Mat dest;
  cvtColor(src, dest,COLOR_BGR2RGB);
  const QImage newImage((uchar*) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
  QPixmap pix = QPixmap::fromImage(newImage);
  if (pixmap != nullptr) {
      scene->removeItem(pixmap);
  }
  pixmap = scene->addPixmap(pix);
}



void MainWindow::setImageGray(const Mat &src)
{

  Mat dest;
  cvtColor(src, dest,COLOR_BGR2RGB);
  const QImage newImage((uchar*) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
  // const QImage newImage(dest.data, dest.cols, dest.rows, QImage::Format_RGB888);

  image = newImage;
  QPixmap pix = QPixmap::fromImage(image);
  scene->removeItem(pixmap);
  pixmap = scene->addPixmap(pix);
}

void MainWindow::onGraphic()
{

}


void MainWindow::onZoomIn()
{
    view->scale(1.2,1.2);
}


void MainWindow::onZoomOut()
{
    view->scale(0.8,0.8);
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
  QString fileName = QString("/data/test_images/01.png");
  if(QFile::exists(fileName))
    {
      mat = imread(fileName.toStdString().c_str(), IMREAD_COLOR);
      dimensionLabel->setText(QString("Image Dimension,  Rows: %1 x Cols: %2").arg(mat.rows).arg(mat.cols));

      setImage(mat);

      const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
      statusBar()->showMessage(message);
    }
}



void MainWindow::onMousePressed(QMouseEvent* event)
{
    qDebug() << "D Mouse Pressed " << event->pos();
    active = 1;
    top_p = view->mapToScene(event->pos());
    bottom_p = top_p + QPoint (100, 100);
    outlinePen.setWidth(2);
    if (rectangle != nullptr) {
        scene->removeItem(rectangle);
    }
    rectangle = new QGraphicsRectItem(QRectF(top_p, bottom_p));
    scene->addItem(rectangle);
}

void MainWindow::onMouseReleased(QMouseEvent* event)
{
    qDebug() << "D Mouse Pressed " << event->pos();
    active = 0;
}

void MainWindow::onMouseMoved(QMouseEvent* event)
{

    if (active == 1) {
        if (rectangle != nullptr) {
            scene->removeItem(rectangle);
        }
        bottom_p = view->mapToScene(event->pos());
        rectangle = new QGraphicsRectItem(QRectF(top_p, bottom_p));
        scene->addItem(rectangle);
    }
}
