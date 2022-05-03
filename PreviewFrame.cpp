#include"PreviewFrame.h"
void PreviewFrame::GetFutureFrame(qint64 time,QString filename){
    QList<PACKET_FRAME> pack_frame_list;
    qDebug()<<"线程运行";
    AVFormatContext *pFormatCtx = avformat_alloc_context();
    int res;
    std::string str = filename.toStdString();
    const char* ch = str.c_str();
    res = avformat_open_input(&pFormatCtx, ch, nullptr, nullptr);
    if (res) {
        return;
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
        return;
    }
    AVCodecContext *pCodecCtxOrig = nullptr;
    // Get a pointer to the codec context for the video stream
    pCodecCtxOrig = pFormatCtx->streams[videoStream]->codec;
    AVCodec *pCodec = nullptr;
    // Find the decoder for the video stream
    pCodec = avcodec_find_decoder(pCodecCtxOrig->codec_id);
    if(pCodec == nullptr) {
        fprintf(stderr, "Unsupported codec!\n");
        return; // Codec not found
    }
    AVCodecContext *pCodecCtx = nullptr;
    // Copy context
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if(avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) {
        fprintf(stderr, "Couldn't copy codec context");
        return; // Error copying codec context
    }
    // Open codec
    if(avcodec_open2(pCodecCtx, pCodec, nullptr)<0) {
        return;// Could not open codec
    }
    AVFrame *pFrameRGB = nullptr;
    pFrameRGB = av_frame_alloc();
//    qint64 current_frame_time = time - 5;
    res = av_seek_frame(pFormatCtx, -1, (time-2) * AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);
    if (res<0) {
        return;
    }
    AVPacket packet;
    while(packet.pts*av_q2d(pFormatCtx->streams[packet.stream_index]->time_base)-this->time<2) {
//        if(this->m_run == 2){
//            qDebug()<<"结束了";
//            avformat_close_input(&pFormatCtx);
//            return;
//        }
        av_read_frame(pFormatCtx, &packet);
//        qDebug()<<"current_time"<<packet.pts*av_q2d(pFormatCtx->streams[packet.stream_index]->time_base);
        if(packet.stream_index == videoStream){
//            qDebug()<<"okok";

//            packet_frame.packet_pointer = &packet;

//            qDebug()<<"timestamp"<<packet.pts*av_q2d(pFormatCtx->streams[packet.stream_index]->time_base);
            res = avcodec_send_packet(pCodecCtx, &packet);
            int gotPicture = avcodec_receive_frame(pCodecCtx, pFrameRGB); //gotPicture = 0 success, a frame was returned
            if(gotPicture == 0) {
                SwsContext* swsContext = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24,
                                          SWS_BICUBIC, nullptr, nullptr, nullptr);
                AVFrame* frameRGB = av_frame_alloc();
                avpicture_alloc((AVPicture*)frameRGB, AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
                sws_scale(swsContext, pFrameRGB->data, pFrameRGB->linesize, 0, pCodecCtx->height, frameRGB->data, frameRGB->linesize);
                QImage image(frameRGB->data[0], pCodecCtx->width, pCodecCtx->height, frameRGB->linesize[0], QImage::Format_RGB888);
//                frame = image.copy();

                PACKET_FRAME packet_frame;
                packet_frame.packet_clock = packet.pts*av_q2d(pFormatCtx->streams[packet.stream_index]->time_base);
//                qDebug()<<"clock"<<packet_frame.packet_clock;
                packet_frame.frame = image.copy();
                pack_frame_list.append(packet_frame);

    //                image.save("D:\\0.jpg");

            }
        }
//        current_frame_time += 1;
    }
//    qDebug()<<"len"<<pack_frame_list.length();
    getClosetPacket(pack_frame_list);
    avformat_close_input(&pFormatCtx);
    return;


//        PACKET_FRAME closet_frame = getClosetPacket(frame_list);
//        packet_pointer = closet_frame.packet_pointer;
//        qDebug()<<"pts"<<packet_pointer->pts;

}

void PreviewFrame::run(){

//    this->m_run = 1;
//    this->reset();
    this->GetFutureFrame(this->time,this->filename);
    emit isDone(this->frame);

}


void PreviewFrame::getClosetPacket(QList<PACKET_FRAME> packet_pointers){
//    for (int i = 0 ;i<packet_pointers.size();i++){
//        qDebug()<<"get_i"<<i;
//        qDebug()<<"clock"<<packet_pointers[i].packet_clock;
//        qDebug()<<"get_distance"<<getDistance(packet_pointers[i].packet_clock,this->time);
//    }

    double min = 1E10;
    qint64 min_index = -1;
    for(int i = 0 ;i<packet_pointers.size();i++){
//        if(m_run == 2){
//            break;
//        }
//        qDebug()<<"this_time"<<this->time;
//        qDebug()<<"min"<<min;
//        qDebug()<<"min_index"<<min_index;
        if (getDistance(packet_pointers[i].packet_clock,this->time)<min){
            min = getDistance(packet_pointers[i].packet_clock,this->time);
            min_index = i;
//            qDebug()<<"clock"<<packet_pointers[i].packet_clock;

        }
    }
//    qDebug()<<"min_index"<<min_index;
    if (min_index != -1 && packet_pointers.length()!=0){

        this->frame = packet_pointers[min_index].frame.copy();
//        qDebug()<<"final_clock"<<packet_pointers[min_index].packet_clock;
//        frame.save("D:\\0.jpg");
        return;
    }

    else{
        this->frame = QImage();
        return;
    }
}

//void PreviewFrame::reset(){
////    this->frame = QImage();
////    this->time = 0;
//}
//void PreviewFrame::stop(){
//    this->m_run = 2;
//}

double PreviewFrame::getDistance(double a,double b){
    return a - b < 0? b - a : a- b;
}


