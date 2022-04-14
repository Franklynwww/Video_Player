#include"VideoSurface.h"
QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(
        QAbstractVideoBuffer::HandleType type) const
{
    if(type == QAbstractVideoBuffer::NoHandle)
    {
        return QList<QVideoFrame::PixelFormat>()
                << QVideoFrame::Format_RGB32;
    }
    else
        return QList<QVideoFrame::PixelFormat>();
}

bool VideoSurface::present(const QVideoFrame & frame)
{
    if(frame.isValid())
    {
        emit presentframe_(frame);
        return true;
    }
    stop();
    return false;
}
