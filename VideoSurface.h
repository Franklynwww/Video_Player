#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H
#include<QAbstractVideoSurface>
class VideoSurface : public QAbstractVideoSurface
{

    Q_OBJECT
public:
    VideoSurface(QObject * parent = Q_NULLPTR);
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(
            QAbstractVideoBuffer::HandleType type = QAbstractVideoBuffer::NoHandle) const;
private slots:
    bool present(const QVideoFrame & frame);
signals:
    void presentframe_(const QVideoFrame & frame);

};
#endif // VIDEOSURFACE_H
