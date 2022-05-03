#ifndef GET_AUDIO_WAVE_H
#define GET_AUDIO_WAVE_H


#include <QThread>
#include <qdebug.h>
#include <QImage>
#include <QQueue>
#include <QFileInfo>
#include<QAudioOutput>
#include"Global_Clock.h"
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




//默认的间隔时间
#define DEFAULT_DIFFER_TIME 40

#define MAX_AUDIO_FRAME_SIZE 192000

//视频音频解码线程
class Audio_WAVE
{
private:
    qint64 ori = 0;
    AVFormatContext *format = nullptr;
    const char *url = "";
    AVCodec *audio_codec = nullptr;
    AVCodecContext * codec = nullptr;
    AVCodecContext * decoder = nullptr;
    int bytes_per_sample;
    AVPacket * packet;
    AVFrame * frame;
    qint64 max = -1;
    qint64 min = 1E10;
//    struct SwrContext *convert_ctx = nullptr;



public:
    void init(QString filename);
    double get_wave_value(int position);
    void stop();
};


#endif // GET_AUDIO_WAVE_H
