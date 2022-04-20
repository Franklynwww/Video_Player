#include"openfilethread.h"

void OpenFileThread::run(){


//    qDebug()<<"thread";
    VideoSurface * videoSurface = new VideoSurface();
    qDebug()<<"position"<<position;
    this->mediaplayer->setVideoOutput(videoSurface);
    this->mediaplayer->setMedia(QUrl(filename));
    this->mediaplayer->setPosition(position);
//    connect(videoSurface, SIGNAL(frameAvailable(QVideoFrame &)), this, SLOT(ProcessFrame(QVideoFrame &)));

}
