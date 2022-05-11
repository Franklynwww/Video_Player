#include "judge_type.h"
int judgetype(QString filename){
    QList<QImage> l;

//    QList<PACKET_FRAME> pack_frame_list;
    qDebug()<<"线程运行";
    AVFormatContext *pFormatCtx = avformat_alloc_context();
    int res;
    std::string str = filename.toStdString();
    const char* ch = str.c_str();
    res = avformat_open_input(&pFormatCtx, ch, nullptr, nullptr);
    if (res) {
        return ERROR;
    }
    avformat_find_stream_info(pFormatCtx, nullptr);
    int videoStream = -1;
    for(int i=0; i<pFormatCtx->nb_streams; i++) {
        if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream=i;
            break;
        }
    }
    if(videoStream == -1) {
        qDebug()<<"wushipin";
        return AUDIO_TYPE;
    }
    AVCodecContext *pCodecCtxOrig = nullptr;
    // Get a pointer to the codec context for the video stream
    pCodecCtxOrig = pFormatCtx->streams[videoStream]->codec;
    AVCodec *pCodec = nullptr;
    // Find the decoder for the video stream
    pCodec = avcodec_find_decoder(pCodecCtxOrig->codec_id);
    if(pCodec == nullptr) {
        fprintf(stderr, "Unsupported codec!\n");
        return AUDIO_TYPE; // Codec not found
    }
    AVCodecContext *pCodecCtx = nullptr;
    // Copy context
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if(avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) {
        fprintf(stderr, "Couldn't copy codec context");
        return AUDIO_TYPE; // Error copying codec context
    }
    // Open codec
    if(avcodec_open2(pCodecCtx, pCodec, nullptr)<0) {
        qDebug()<<"open fail";
        return AUDIO_TYPE;// Could not open codec
    }

    AVFrame *pFrameRGB = nullptr;
    pFrameRGB = av_frame_alloc();
    AVPacket packet;
    int count = 0;
    int limit = 50;
    int flag = 0;
    while(count < limit && av_read_frame(pFormatCtx, &packet) >= 0) {
        qDebug()<<"count"<<count;
        av_read_frame(pFormatCtx, &packet);
        count += 1;
        if(packet.stream_index == videoStream){
            flag = 1;
            res = avcodec_send_packet(pCodecCtx, &packet);
            int gotPicture = avcodec_receive_frame(pCodecCtx, pFrameRGB); //gotPicture = 0 success, a frame was returned
            if(gotPicture == 0) {
                SwsContext* swsContext = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24,
                                          SWS_BICUBIC, nullptr, nullptr, nullptr);
                AVFrame* frameRGB = av_frame_alloc();
                avpicture_alloc((AVPicture*)frameRGB, AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
                sws_scale(swsContext, pFrameRGB->data, pFrameRGB->linesize, 0, pCodecCtx->height, frameRGB->data, frameRGB->linesize);
                QImage image(frameRGB->data[0], pCodecCtx->width, pCodecCtx->height, frameRGB->linesize[0], QImage::Format_RGB888);
                l.append(image.copy());
                qDebug()<<"size"<<l.size();
            }
        }
    }
    if(flag == 0){
        return AUDIO_TYPE;
    }
    avformat_close_input(&pFormatCtx);
    return VIDEO_TYPE;
}
