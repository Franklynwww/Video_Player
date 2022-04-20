#ifndef UTILS_H
#define UTILS_H


#include <stdio.h>
#include <QDebug>

extern "C"//包含C文件头
{
#include "libavformat/avformat.h"
}
#include<QString>
bool isValidVideoFile(QString filename);
QString transfer_to_std_time(qint64 miniseconds);
void pngTomp4_2() ;
#endif // UTILS_H
