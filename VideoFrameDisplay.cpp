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

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    painter.setBrush(Qt::black);
    painter.drawRect(0,0,this->width(),this->height()); //先画成黑色

    if (mImage.size().width() <= 0) return;

    //将图像按比例缩放成和窗口一样大小
    QImage img = mImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation); //这里效率比较低下  还不知道如何优化

    //画面旋转
    if(m_nRotateDegree > 0)
    {
        QTransform matrix;
        matrix.rotate(m_nRotateDegree);
        img = img.transformed(matrix, Qt::SmoothTransformation);
    }

    int x = this->width() - img.width();
    int y = this->height() - img.height();
//    qDebug()<<x;
//    qDebug()<<y;

    x /= 2;
    y /= 2;




    painter.drawImage(QPoint(x,y),img); //画出图像
}


void VideoFrameDisplay::slotSetOneFrame(QImage img,double video_clock)
{

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
                //    qDebug()<<"在花了";
                      src_mImage =mImage = img;
                 //    qDebug()<<img.size();
                 //    img.save("D:\\images\\0.jpg");
                      update(); //调用update将执行 paintEvent函数
//}
//            }
//            else//视频时钟比主时钟慢，则丢弃该帧
//            {
////                    msleep(1);
////                    av_packet_unref(&avPacket);
////                    av_freep(&avPacket);
//                return;
//            }



}

void VideoFrameDisplay::slotSetOneAudioFrame(QByteArray byt,double audio_clock){
//    qDebug()<<"在播了";
    int writeBytes = qMin(byt.length(), audioOutput->bytesFree());
//    qDebug()<<"writeBytes"<<writeBytes;
    streamOut->write(byt.data(), writeBytes);
    byt = byt.right(byt.length() - writeBytes);

//    set_clock(&play_clock_s,audio_clock,0);

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
