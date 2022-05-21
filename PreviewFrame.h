#ifndef PREVIEWFRAME_H
#define PREVIEWFRAME_H
#include<exception>
#include <QThread>
#include <qdebug.h>
#include <QImage>
#include <QQueue>
#include <QFileInfo>
#include<QAudioOutput>
#include<QTimer>
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
using namespace std;


//struct AUDIO_FRAME
//{
//    QByteArray audio;
//    double audio_clock;

//};

struct IMAGE_FRAME_2
{
    QImage image;
    double video_clock;

};

//视频预览线程
class PreviewFrame:public QThread
{
    Q_OBJECT
public:
    //构造函数
    PreviewFrame();
    ~PreviewFrame();
//    QTimer* m_ptimer;




protected:
    void run() override;
    void GetFutureFrame(qint64 time);
    void getClosetPacket(QList<IMAGE_FRAME_2>&);



signals:
    void isDone(QImage);
//    void notDone();
    void changeCallBack();
    void begintoread();
    void finishedread();


public:
    QString filename;
    qint64 time;
    QImage frame;
    int m_run;
    int before_start(QString filename);
    double getDistance(double a,double b);
    static int interrupt_cb(void *ctx);
    int is_keyframe(AVCodec *dec, AVPacket* pkt);
    int is_keyframe_h264(AVPacket* pkt);
    static bool callback1;
//    int m_run = 0;
    static int count;
//    double duration;

//    void reset();
//    void stop();
    QTimer* m_pTimer;
    AVFormatContext * format_ctx;
    AVCodec *video_pCodec;
    AVCodecContext * decoder;
    int video_height;
    int video_width;
    int video_stream_index = -1;
    AVFrame * SRC_VIDEO_pFrame;
    AVFrame * RGB24_pFrame;
    SwsContext * img_convert_ctx;
    uint8_t* out_buffer_rgb;

private slots:
    void on_timer_timeout();
    void setCallBack();
//    void timeout();
private:
    char m_MediaFile[1024];
};



#endif // PREVIEWFRAME_H
