#ifndef PREVIEWFRAME_H
#define PREVIEWFRAME_H

#include <QThread>
#include <qdebug.h>
#include <QImage>
#include <QQueue>
#include <QFileInfo>
#include<QAudioOutput>
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


//struct AUDIO_FRAME
//{
//    QByteArray audio;
//    double audio_clock;

//};

struct PACKET_FRAME
{
    QImage frame;
    double packet_clock;

};

//视频预览线程
class PreviewFrame:public QThread
{
    Q_OBJECT
public:
    //构造函数
//    PreviewFrame();
//    ~PreviewFrame();




protected:
    void run() override;
    void GetFutureFrame(qint64 time,QString filename);
    void getClosetPacket(QList<PACKET_FRAME>);


signals:
    void isDone(QImage);

public:
    QString filename;
    qint64 time;
    QImage frame;
    double getDistance(double a,double b);
//    int m_run;

//    void reset();
//    void stop();


};

#endif // PREVIEWFRAME_H
