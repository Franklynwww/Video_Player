#ifndef GLOBAL_CLOCK_H
#define GLOBAL_CLOCK_H
#include "PLAY_CLOCK_S.h"
#include<QMutex>
static PALY_CLOCK_S play_clock_s;
static QMutex video_mutex;
static QMutex audio_mutex;
static QMutex pre_frame_mutex;
static QMutex pre_frame_internal_mutex;
//static qint64 video_time = 0;
//static qint64 audio_time = 0;
//static bool video_mutex;
//static bool audio_mutex;
#endif // GLOBAL_CLOCK_H
