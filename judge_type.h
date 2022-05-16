#ifndef JUDGE_TYPE_H
#define JUDGE_TYPE_H
#include <QString>
#include <QImage>
#include<QDebug>
extern "C" {
#include <libavutil/opt.h>
#include <libavutil/mem.h>
#include <libavutil/fifo.h>
#include <libavutil/pixfmt.h>
#include <libavutil/log.h>
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
#include <libavfilter/avfilter.h>
#include <libavfilter/buffersrc.h>
#include <libavfilter/buffersink.h>
}
#define AUDIO_TYPE 0
#define VIDEO_TYPE 1
#define ERROR 2

int judgetype(QString filename);
int ori_judgetype(QString filename);
#endif // JUDGE_TYPE_H
