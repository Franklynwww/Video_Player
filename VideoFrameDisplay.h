#ifndef VideoFrameDisplay_H
#define VideoFrameDisplay_H

#include <QWidget>
#include <QPaintEvent>
#include <QDebug>
#include <QLabel>
#include <QTime>
#include<QAudioOutput>
#include<QTimer>

#include<QCoreApplication>

///显示视频用的widget
///这个仅仅是显示视频画面的控件
class VideoFrameDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit VideoFrameDisplay(QWidget *parent = 0);
    ~VideoFrameDisplay();

    //画面旋转度数
    int m_nRotateDegree;
    double volumn;
    void Set_Rotate(int Rotate);
    //获取当前图像
    QImage GetImage();

   // QLabel *time_lable;
    double video_pos;
    bool m_pause_state=false;
    qint64 m_play_time=0;
    qint64 m_start_time=0; //开始的时间
    qint64 m_pos_time=0;
    QImage src_mImage;
    QImage mImage; //记录当前的图像
    int type;
    bool paint_finished;
    int i = 0;

    QAudioOutput        *audioOutput;
    QIODevice           *streamOut;

//    QTimer*  m_pTimer_video;
//    QTimer*  m_pTimer_audio;

signals:
    void s_VideoWidgetEvent(int type);
    void positionchanged(qint64 pos);
    void main_sleep();

    void callaudiosleep(qint64);
    void callvideosleep(qint64);

    void change_audio_s_video_time(qint64);

protected:
    void paintEvent(QPaintEvent *event);

    void mouseDoubleClickEvent(QMouseEvent *e);



public slots:
    ///播放器相关的槽函数
    void slotSetOneFrame(QImage,double);
    void slotSetOneAudioFrame(QByteArray,double);
    void threadStarted();
    void unlock_mutex();
//    void on_timer_timeout_audio();
//    void on_timer_timeout_video();

};

#endif // VideoFrameDisplay_H
