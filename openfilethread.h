#ifndef OPENFILETHREAD_H
#define OPENFILETHREAD_H

#include<QThread>
#include<QString>
#include<QMediaPlayer>
#include"VideoSurface.h"

class OpenFileThread:public QThread{
    Q_OBJECT
public:
    int position;
    QString filename;
    QMediaPlayer * mediaplayer;
    void run() override;


};

#endif // OPENFILETHREAD_H
