#ifndef UTILS_H
#define UTILS_H


#include <stdio.h>
#include <QDebug>

#define AUDIO 0
#define VIDEO 1

extern "C"//包含C文件头
{
#include "libavformat/avformat.h"
}
#include<QString>
bool isValidVideoFile(QString filename);
bool isVideoOrAudio(QString filename);
QString transfer_to_std_time(qint64 miniseconds);
void pngTomp4_2();
#endif // UTILS_H
