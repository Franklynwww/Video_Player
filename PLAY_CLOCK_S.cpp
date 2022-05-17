
#include"PLAY_CLOCK_S.h"
// 返回值：返回上一帧的pts更新值(上一帧pts+流逝的时间)
double get_clock(PALY_CLOCK_S *c)
{

    if (c->m_Paused)
    {
        return c->m_Pts;
    }
    else
    {
        double time = av_gettime_relative() / 1000000.0;
        double ret = c->m_PtsDrift + time;   // 展开得： c->pts + (time - c->last_updated)
        return ret;
    }
}

void set_clock_at(PALY_CLOCK_S *c, double pts, int serial, double time)
{
    c->m_Pts = pts;
    c->m_LastUpdated = time;
    c->m_PtsDrift = c->m_Pts - time;
    c->m_Serial = serial;
}

void set_clock(PALY_CLOCK_S *c, double pts, int serial)
{
    double time = av_gettime_relative() / 1000000.0;
    set_clock_at(c, pts, serial, time);
}


void init_clock(PALY_CLOCK_S *c)
{
    c->m_Speed = 1.0;
    c->m_Paused = 0;

    set_clock(c, NAN, -1);
}
