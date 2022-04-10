#ifndef OPENFILETHREAD_H
#define OPENFILETHREAD_H

#include<QThread>
#include<QString>

class OpenFileThread:public QThread{
    Q_OBJECT
public:
    int signal;
    QString filename;

};

#endif // OPENFILETHREAD_H
