#ifndef REVERSEDECODE_AUDIO_H
#define REVERSEDECODE_AUDIO_H

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


struct AUDIO_FRAME
{
    QByteArray audio;
    double audio_clock;

};


//默认的间隔时间
#define DEFAULT_DIFFER_TIME 40

#define MAX_AUDIO_FRAME_SIZE 192000

//视频音频解码线程
class ReverseDecode_Audio:public QThread
{
    Q_OBJECT
public:
    //构造函数
    ReverseDecode_Audio();
    ~ReverseDecode_Audio();
    char m_MediaFile[1024];

    int m_run; //1表示运行 0表示停止 2表示暂停
    double m_n64CurrentSeekPos = 0;  //当前seek位置
    double m_seek=0;
    double m_endSeekPos = 0; //结束位置
    bool is_CurrentSeekPos = 0; //1需要跳转 0不需要
    bool no_video_signal = false;

    void SetSate(int run);
    int GetSate();
    void SetSeekPos(qint64 pos);
    void PausePlay();
    void StopPlay();
    void LogSend(QString text);

    bool finished = false;

    //加载视频文件
    int LoadVideoFile(QString media);

    //释放内存
    void FreeRAM();


    //解码音频帧
    int DecodDataPack2();

    //获取总时间
    qint64 GetDuration();

    //获取两帧相差的时间
    qint32 GetDifferTimer() { return m_DifferTime; }





protected:
    void run();
    int StartPlayAudio();


signals:
    void positionChanged2(qint64 ms);
    void SendOneAudioFrame(QByteArray); //输出信号
    void ss_ReversePlayFinish(); //倒放完成..--暂停或者停止的时候发出信号
    void isDone2();
    void started2();

private:
    int video_width = 0;
    int video_height = 0;
//    QList <struct IMAGE_FRAME> video_pack;
    QList<struct AUDIO_FRAME> audio_pack;
//    QList <struct IMAGE_FRAME> over_pack; //上次解码没有用完的包
    QList<struct AUDIO_FRAME> over_pack;
    AVFormatContext *format_ctx = nullptr;
    int video_stream_index = -1;
    AVFrame *RGB24_pFrame = nullptr;
    AVFrame *SRC_Audio_pFrame = nullptr;
    uint8_t *out_buffer_rgb = nullptr;
    struct SwsContext *img_convert_ctx = nullptr;  //用于解码后的视频格式转换


    int audio_stream_index = -1;
    AVCodecParameters   *aCodecParameters;
     AVCodec             *aCodec;
     AVCodecContext      *aCodecCtx;


     uint64_t out_channel_layout;
     AVSampleFormat out_sample_fmt;
     int out_sample_rate;
     int out_channels;
     uint8_t *out_buffer_audio = nullptr;



    bool seek_state = 0; //偏移状态

    qint32 m_DifferTime= DEFAULT_DIFFER_TIME; //两帧相差的时间

    qint64 m_oldPosMs; //保存上一次的帧时间

    QString file_suffix;
public slots:
    void no_video_handle();
};

#endif // REVERSEDECODE_AUDIO_H
