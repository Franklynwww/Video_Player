#include "VideoFrameDisplay.h"
#include "ReverseDecode.h"

#include <QPainter>

VideoFrameDisplay::VideoFrameDisplay(QWidget *parent) :
    QWidget(parent)
{
    m_nRotateDegree=0;
    this->setMouseTracking(true);



}

VideoFrameDisplay::~VideoFrameDisplay()
{

}

void VideoFrameDisplay::Set_Rotate(int Rotate)
{
    m_nRotateDegree=Rotate;
}

void VideoFrameDisplay::paintEvent(QPaintEvent *event)
{

//    qDebug()<<"画的大小位"<<mImage.size();
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    painter.setBrush(Qt::black);
    painter.drawRect(0,0,this->width(),this->height()); //先画成黑色


    if (mImage.size().width() <= 0) {

        return;};


    //将图像按比例缩放成和窗口一样大小
//    qDebug()<<"test point在这里1！！！！";
    QImage img = mImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); //这里效率比较低下  还不知道如何优化

//    qDebug()<<"test point在这里2！！！！";
    //画面旋转
    if(m_nRotateDegree > 0)
    {
        QTransform matrix;
        matrix.rotate(m_nRotateDegree);
        img = img.transformed(matrix, Qt::SmoothTransformation);
    }
//    qDebug()<<"test point在这里3！！！！";

    int x = this->width() - img.width();
    int y = this->height() - img.height();
//    qDebug()<<x;
//    qDebug()<<y;
//    qDebug()<<"test point在这里4！！！！";

    x /= 2;
    y /= 2;

//    qDebug()<<"test point在这里5！！！！";



    painter.drawImage(QPoint(x,y),img); //画出图像
}


void VideoFrameDisplay::slotSetOneFrame(QImage img,double video_clock)
{



//    qDebug()<<"locked"<<video_mutex.tryLock();
//    video_mutex.lock();

    qDebug()<<"video pos"<<video_clock;
    emit change_audio_s_video_time(video_clock*1000);

//    video_time = video_clock * 1000;
//    if(audio_time>video_time){
//        emit callvideosleep(audio_time-video_time);
//    }
//    if(audio_time >= 0)
//    if(video_time - audio_time > 100 || video_time - audio_time < -100){
//        qDebug()<<"audio要休眠一下";
//    }


//    if(video_time - audio_time > 1){
//        emit callaudiosleep(video_time - audio_time);
//    }

//            double audioTime = get_clock(&play_clock_s);

            //如果读取到无效的时钟时间的话则continue
//                if(isnan(audioTime))
//                {
//                    usleep(1000*1000/g_MedieInfo.m_FrameRate);
//                    av_packet_unref(&avPacket);
//                    av_freep(&avPacket);
//                    continue;
//                }

            //qDebug()<<"Video Time "<<videoPts<<" Get Audio Time "<<audioTime;

            //计算视频时钟与主时钟的差值
//            int DiffTimeMs = video_clock*1000 - audioTime*1000;

//            qDebug()<<"diffentimeMS"<<DiffTimeMs;
//            if(DiffTimeMs >= 0)//视频时钟比主时钟快，则休眠
//            {
//                QThread::msleep(DiffTimeMs);
                    qDebug()<<"在花了";
                      src_mImage = mImage = img;
                     qDebug()<<img.size();
                 //    img.save("D:\\images\\0.jpg");
                      repaint(); //调用update将执行 paintEvent函数
//}
//            }
//            else//视频时钟比主时钟慢，则丢弃该帧
//            {
////                    msleep(1);
////                    av_packet_unref(&avPacket);
////                    av_freep(&avPacket);
//                return;
//            }

//              video_mutex = false;
              emit positionchanged(video_clock * 1000);
//              qDebug()<<"video_mutex"<<video_mutex;
//              while(!video_mutex);
//       m_pTimer_video->start(40);
//                      emit main_sleep();
//         video_mutex.unlock();


}

void VideoFrameDisplay::slotSetOneAudioFrame(QByteArray byt,double audio_clock){
    qDebug()<<"在播了";

//    audio_mutex.lock();
    qDebug()<<"audio pos"<<audio_clock;
//    audio_time = audio_clock * 1000;
//    if(video_time>=audio_time){
//        emit callaudiosleep(video_time - audio_time);
//    }
//    else{
//        return;
//    }
//    if(audio_time - video_time > 0.01){
//        qDebug()<<"video你休息一下";
//        emit callvideosleep((audio_time - video_time)*1000);
////        return;
//    }
    int writeBytes = qMin(byt.length(), audioOutput->bytesFree());
//    qDebug()<<"writeBytes"<<writeBytes;
//    qDebug()<<"音量为"<<audioOutput->volume();

//    qDebug()<<"调整后的音量为"<<this->volumn;

    audioOutput->setVolume(this->volumn);
    streamOut->write(byt.data(), writeBytes);
    byt = byt.right(byt.length() - writeBytes);
    if(type == 0){
//        audio_mutex = false;
        emit positionchanged(audio_clock * 1000);
//        while(!audio_mutex);
    }

//    emit main_sleep();
//    audio_mutex.unlock();
//    set_clock(&play_clock_s,audio_clock,0);

//    QEventLoop eventloop;
//    QTimer::singleShot(40, &eventloop, SLOT(quit()));
//    eventloop.exec();

//    m_pTimer_audio->stop();
//    m_pTimer_audio->start(40);

}

/*
工程: QtAV_VideoPlayer
日期: 2021-03-24
作者: DS小龙哥
环境: win10 QT5.12.6 MinGW32
功能: 获取原图数据
*/
QImage VideoFrameDisplay::GetImage()
{
    return src_mImage.copy();
}

/*
工程: QtAV_VideoPlayer
日期: 2021-03-25
作者: DS小龙哥
环境: win10 QT5.12.6 MinGW32
功能: 鼠标双击事件
*/
void VideoFrameDisplay::mouseDoubleClickEvent(QMouseEvent *e)
{
    emit s_VideoWidgetEvent(1);
}

void VideoFrameDisplay::threadStarted(){
    QAudioFormat fmt;
    fmt.setSampleRate(44100);
    fmt.setSampleSize(16);
    fmt.setChannelCount(2);
    fmt.setCodec("audio/pcm");
    fmt.setByteOrder(QAudioFormat::LittleEndian);
    fmt.setSampleType(QAudioFormat::SignedInt);

    audioOutput = new QAudioOutput(fmt);
    streamOut = audioOutput->start();
}

void VideoFrameDisplay::unlock_mutex(){
//    video_mutex.tryLock();
//    audio_mutex.tryLock();
//    video_mutex.unlock();
//    audio_mutex.unlock();
}

//void VideoFrameDisplay::on_timer_timeout_audio(){
//    qDebug()<<"audo解锁";
//    audio_mutex.unlock();
//}

//void VideoFrameDisplay::on_timer_timeout_video(){
//    video_mutex.unlock();
//}
