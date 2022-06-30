#include "mainwindow.h"
#include <QApplication>
#include <QAudioDevice>
#include <QCameraDevice>
#include <QTextStream>
#include <QMediaDevices>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextStream out(stdout);
    
    MainWindow w;
    w.show();

    return a.exec();
}
