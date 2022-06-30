#include <QtWidgets>
#include <QLabel>
#include <QVBoxLayout> 
#include <QGridLayout>
#include <QHBoxLayout>
#include <QIcon>
#include "mainwindow.h"




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

  /* Content Layout */
  contentLayout = new QVBoxLayout(content);

  imageLabel = new QLabel();
  contentLayout->addWidget(imageLabel);


  /* Root Layout */
  QVBoxLayout *rootLayout = new QVBoxLayout(root);
  rootLayout->addWidget(top);
  rootLayout->addWidget(content);
  setCentralWidget(root); 
}

MainWindow::~MainWindow()
{
  
}

void MainWindow::onStart()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Open Input Image", QDir::currentPath(), "Images (*.jpg *.png *.bmp)");
    if(QFile::exists(fileName))
    {

    }
}

void MainWindow::onStop()
{
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
