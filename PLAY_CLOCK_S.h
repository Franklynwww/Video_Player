#ifndef PLAY_CLOCK_S_H
#define PLAY_CLOCK_S_H
extern "C" {
#include <libavutil/time.h>
}

#include<cmath>

typedef struct
{
    double m_Pts;                     // 当前帧(待播放)显示时间戳，播放后，当前帧变成上一帧
    double m_PtsDrift;               // 当前帧显示时间戳与当前系统时钟时间的差值
    double m_LastUpdated;            // 当前时钟(如视频时钟)最后一次更新时间，也可称当前时钟时间
    double m_Speed;                   // 时钟速度控制，用于控制播放速度
    int m_Serial;                     // 播放序列，所谓播放序列就是一段连续的播放动作，一个seek操作会启动一段新的播放序列
    int m_Paused;                     // 暂停标志
}PALY_CLOCK_S;

double get_clock(PALY_CLOCK_S *c);
void set_clock_at(PALY_CLOCK_S *c, double pts, int serial, double time);
void set_clock(PALY_CLOCK_S *c, double pts, int serial);
void init_clock(PALY_CLOCK_S *c);


#endif // PLAY_CLOCK_S_H
