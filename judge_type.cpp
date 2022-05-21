#include "judge_type.h"
int judgetype(QString filename){

    filename = filename.toLower();
    int lastindex = filename.lastIndexOf(".");
    QString type = "";
    for (int i = lastindex+1;i<filename.length();i++){
        type += filename[i];
    }
    if (type == "mkv" || type == "mp4" || type == "avi" || type == "wmv" || type == "mpg" || type == "mpeg" || type == "flv" || type == "rmvb" || type == "rm" || type == "mov"){
        return VIDEO_TYPE;
    }
    else{if(type == "wav" || type == "mp3" || type == "wma" || type == "ram"){
            return AUDIO_TYPE;
        }
    }


}

int ori_judgetype(QString filename){
//    return judgetype(filename);
        QList<QImage> l;
    //    QList<PACKET_FRAME> pack_frame_list;
        qDebug()<<"线程运行";
        AVFormatContext *pFormatCtx = avformat_alloc_context();
        int res;
        std::string str = filename.toStdString();
        const char* ch = str.c_str();
        res = avformat_open_input(&pFormatCtx, ch, nullptr, nullptr);
        if (res) {
            avformat_close_input(&pFormatCtx);
            avformat_free_context(pFormatCtx);
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
            avformat_close_input(&pFormatCtx);
            avformat_free_context(pFormatCtx);
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
            avformat_close_input(&pFormatCtx);
            avformat_free_context(pFormatCtx);
            return AUDIO_TYPE; // Codec not found
        }
        AVCodecContext *pCodecCtx = nullptr;
        // Copy context
        pCodecCtx = avcodec_alloc_context3(pCodec);
        if(avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) {
            fprintf(stderr, "Couldn't copy codec context");
            avformat_close_input(&pFormatCtx);
            avformat_free_context(pFormatCtx);
            return AUDIO_TYPE; // Error copying codec context
        }
        // Open codec
        if(avcodec_open2(pCodecCtx, pCodec, nullptr)<0) {
            qDebug()<<"open fail";
            avformat_close_input(&pFormatCtx);
            avformat_free_context(pFormatCtx);
            return AUDIO_TYPE;// Could not open codec
        }

        AVFrame *pFrameRGB = nullptr;
        pFrameRGB = av_frame_alloc();
        AVPacket packet;
        int count = 0;
        int limit = 500;
        int flag = 0;
        while(count < limit && av_read_frame(pFormatCtx, &packet) >= 0) {
//            qDebug()<<"count"<<count;
            av_read_frame(pFormatCtx, &packet);
            count += 1;
            qDebug()<<"count in type judge"<<count;
            if(packet.stream_index == videoStream){
                flag = 1;
            av_packet_unref(&packet);
            }
        }
        if(flag == 0){
            avformat_close_input(&pFormatCtx);
            avformat_free_context(pFormatCtx);
            return AUDIO_TYPE;
        }
        avformat_close_input(&pFormatCtx);
        avformat_free_context(pFormatCtx);
        return VIDEO_TYPE;
}
