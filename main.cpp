#include "mainwindow.h"
#include <QApplication>
#include <QAudioDevice>
#include <QCameraDevice>
#include <QTextStream>
#include <QMediaDevices>


QString positionToString(QCameraDevice::Position position)
{
    switch (position) {
        case QCameraDevice::BackFace:
            return "BackFace";
        case QCameraDevice::FrontFace:
            return "FrontFace";
        default:
            return "Unspecified";
    }
}


void printVideoDeviceInfo(QTextStream &out, const QCameraDevice &cameraDevice)
{
    const auto isDefault = cameraDevice.isDefault() ? "Yes" : "No";
    const auto position = cameraDevice.position();
    const auto photoResolutions = cameraDevice.photoResolutions();
    const auto videoFormats = cameraDevice.videoFormats();

    out.setFieldWidth(30);
    out.setFieldAlignment(QTextStream::AlignLeft);
    out << "Name: " << cameraDevice.description() << qSetFieldWidth(0) << Qt::endl;
    out.setFieldWidth(30);
    out << "Id: " <<  QString::fromLatin1(cameraDevice.id()) << qSetFieldWidth(0) << Qt::endl;
    out.setFieldWidth(30);
    out << "Default: " <<  isDefault << qSetFieldWidth(0) << Qt::endl;
    out.setFieldWidth(30);
    out << "Position: " << positionToString(position) << qSetFieldWidth(0) << Qt::endl;
    out.setFieldWidth(30);
    out << "Photo Resolutions: ";
    for (auto &resolution: photoResolutions) {
        QString s = QString("%1x%2").arg(resolution.width()).arg(resolution.height());
        out << qSetFieldWidth(0) << s << ", ";
    }
    out.setFieldWidth(10);
    out << Qt::endl << Qt::endl;
    out << "Supported Video Formats: " << qSetFieldWidth(0) << Qt::endl;
    for (auto &format: videoFormats) {
        out.setFieldWidth(30);
        QString s = QString("%1x%2").arg(format.resolution().width()).arg(format.resolution().height());
        out << "Resolution: " << s << qSetFieldWidth(0) << Qt::endl;
        out.setFieldWidth(30);
        out << "Frame Rate: " << qSetFieldWidth(0) << "Min:" << format.minFrameRate() << " Max:" << format.maxFrameRate() << Qt::endl;
    }

    out << Qt::endl;

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextStream out(stdout);
    const auto videoInputDevices = QMediaDevices::videoInputs();

    out << Qt::endl << "Video devices detected: " << Qt::endl;
    for (auto &cameraDevice : videoInputDevices)
        printVideoDeviceInfo(out, cameraDevice);    
    
    MainWindow w;
    w.show();

    return a.exec();
}
