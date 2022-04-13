#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

extern "C"
{
#include "libavcodec/avcodec.h"
}

int main(int argc, char *argv[])
{
    qDebug()<<av_version_info();
    qDebug()<<avcodec_configuration();
    QTextCodec *code = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(code);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
