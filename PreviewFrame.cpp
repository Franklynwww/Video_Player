#include"PreviewFrame.h"

bool PreviewFrame::callback1 = false;
int PreviewFrame::count = 0;


PreviewFrame::PreviewFrame(){

    av_register_all();
}

PreviewFrame::~PreviewFrame(){
    if (img_convert_ctx)sws_freeContext(img_convert_ctx);
    if (SRC_VIDEO_pFrame) av_frame_free(&SRC_VIDEO_pFrame);
    if (RGB24_pFrame) av_frame_free(&RGB24_pFrame);
//    if (out_buffer_rgb)free(out_buffer_rgb);

    SRC_VIDEO_pFrame = nullptr;
    RGB24_pFrame = nullptr;
    img_convert_ctx = nullptr;
    out_buffer_rgb = nullptr;

//    video_stream_index = -1;


    if(decoder){
        avcodec_close(decoder);
    }

    if (format_ctx)
    {
        avformat_close_input(&format_ctx);//释放解封装器的空间，以防空间被快速消耗完
        avformat_free_context(format_ctx);
    }

}

int PreviewFrame::before_start(QString filename){
    video_stream_index = -1;
    strncpy(m_MediaFile, filename.toUtf8().data(), sizeof(m_MediaFile));

    QFileInfo info(m_MediaFile);

    //得到后缀
    QString file_suffix=info.suffix();
    qDebug()<<"suffix"<<file_suffix;

    format_ctx = avformat_alloc_context();
    if (avformat_open_input(&format_ctx, m_MediaFile, nullptr, nullptr) != 0)
    {
//        LogSend(tr("无法打开视频文件: %1").arg(m_MediaFile));
        return -1;
    }
    qDebug()<<"Liushuliang"<<format_ctx->nb_streams;

    //读取媒体文件的数据包以获取流信息
    if (avformat_find_stream_info(format_ctx, nullptr) < 0)
    {
//        LogSend(tr("无法获取流信息.\n"));
        return -1;
    }


    ////////////////////////////////////////////////////////
//    if(file_suffix == "mov" || file_suffix == "wmv"||file_suffix == "mp4"||file_suffix == "mp3"){
//        AVFormatContext *pFormatCtx = avformat_alloc_context();
//        int res;
//        std::string str = filename.toStdString();
//        const char* ch = str.c_str();

////        AVFormatContext *pAVFormatContext = avformat_alloc_context();//申请一个AVFormatContext结构的内存,并进行简单初始化
////            AVDictionary* options = NULL;
////            av_dict_set(&options, "buffer_size", "102400", 0); //设置缓存大小，1080p可将值调大
////            av_dict_set(&options, "rtsp_transport", "tcp", 0); //默认以udp方式打开，改为tcp
////            av_dict_set(&options, "stimeout", "2000000", 0); //设置超时断开连接时间，单位微秒
////            av_dict_set(&options, "max_delay", "500000", 0); //设置最大时延
//        res = avformat_open_input(&pFormatCtx, ch, nullptr, nullptr);
//        if (res) {
//            qDebug()<<"打开上下文失败";
//            return;
//        }
//        avformat_find_stream_info(pFormatCtx, nullptr);
//        int videoStream = -1;
//        for(int i=0; i<pFormatCtx->nb_streams; i++) {
//            if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
//                videoStream=i;
//                break;
//            }
//        }
//        if(videoStream == -1) {
//            return;
//        }
//        AVCodecContext *pCodecCtxOrig = nullptr;
//        // Get a pointer to the codec context for the video stream
//        pCodecCtxOrig = pFormatCtx->streams[videoStream]->codec;
//        AVCodec *pCodec = nullptr;
//        // Find the decoder for the video stream
//        pCodec = avcodec_find_decoder(pCodecCtxOrig->codec_id);
//        if(pCodec == nullptr) {
//            fprintf(stderr, "Unsupported codec!\n");
//            return; // Codec not found
//        }

//        AVCodecContext *pCodecCtx = nullptr;
//        // Copy context
//        pCodecCtx = avcodec_alloc_context3(pCodec);
//        if(avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) {
//            fprintf(stderr, "Couldn't copy codec context");
//            return; // Error copying codec context
//        }
//        // Open codec
//        if(avcodec_open2(pCodecCtx, pCodec, nullptr)<0) {
//            return;// Could not open codec
//        }
//        AVFrame *pFrameRGB = nullptr;
//        pFrameRGB = av_frame_alloc();
//    //    qint64 current_frame_time = time - 5;

//        res = av_seek_frame(pFormatCtx, -1, (time-2) * AV_TIME_BASE, AVSEEK_FLAG_ANY);
//        if (res<0) {
//            return;
//        }

    ////////////////////////////////////////////////////////

    for (int i = 0; i < format_ctx->nb_streams; ++i)
    {
        const AVStream* stream = format_ctx->streams[i];
        if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            //查找解码器
            video_pCodec = avcodec_find_decoder(stream->codecpar->codec_id);
            //打开解码器
            decoder = avcodec_alloc_context3(video_pCodec);
            avcodec_parameters_to_context(decoder, stream->codecpar);

            if (avcodec_open2(decoder, video_pCodec, nullptr) != 0)
            {
                qDebug()<<("解码器打开失败.\n");
                return -1;
            }
            video_stream_index = i;
            //得到视频帧的宽高
            video_width = stream->codecpar->width;
            video_height = stream->codecpar->height;
            if(video_width<=0 || video_height<=0 || video_width>=3000||video_height>=2000){
                return -1;
            }
            qDebug()<<"h_w"<<video_height<<video_width;

            qDebug()<<"视频帧的尺寸(以像素为单位): (宽X高),像素格式:"<<stream->codecpar->width<<stream->codecpar->height<<stream->codecpar->format;


        }
    }

    qDebug()<<"test point111111";
    qDebug()<<"video_stream_index"<<video_stream_index;
    if (video_stream_index == -1)
    {
        qDebug()<<("没有检测到视频流.\n");
        return -1;
    }

    AVRational frameRate = format_ctx->streams[video_stream_index]->avg_frame_rate;


    /*设置视频转码器*/
    SRC_VIDEO_pFrame = av_frame_alloc();
    RGB24_pFrame = av_frame_alloc();// 存放解码后YUV数据的缓冲区

    //将解码后的YUV数据转换成RGB24
    img_convert_ctx = sws_getContext(video_width, video_height,
        decoder->pix_fmt, video_width, video_height,
        AV_PIX_FMT_RGB24, SWS_BICUBIC, nullptr, nullptr, nullptr);

    //计算RGB图像所占字节大小
    int numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, video_width, video_height);

    //申请空间存放RGB图像数据
    out_buffer_rgb = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

    // avpicture_fill函数将ptr指向的数据填充到picture内,但并没有拷贝,只是将picture结构内的data指针指向了ptr的数据
    avpicture_fill((AVPicture *)RGB24_pFrame, out_buffer_rgb, AV_PIX_FMT_RGB24,
        video_width, video_height);

    return 0;

}



void PreviewFrame::GetFutureFrame(qint64 time){

    qDebug()<<"time"<<time;


    AVPacket pkt;

//    av_init_packet(&pkt);

//    pre_frame_mutex.lock();
    av_seek_frame(format_ctx, -1, (this->time - 1)*AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);
//    pre_frame_mutex.unlock();

    QList<IMAGE_FRAME_2> frame_pack;

//    double min = 1E10;

    while (1)
    {

        pre_frame_internal_mutex.lock();
        int r = av_read_frame(format_ctx, &pkt);
        if(r<0){
            av_packet_unref(&pkt);
            pre_frame_internal_mutex.unlock();
            break;

        }
//        qDebug()<<"m_run"<<m_run;
//        if(m_run == 2){
//            return;
//        }

//        pre_frame_mutex.lock();
//        int r = ;
//        pre_frame_mutex.unlock();
//        if(r<0){
//            break;
//        }

        qDebug()<<"test point";

        if (pkt.stream_index == video_stream_index){
             //当前时间
              double video_clock = av_q2d(format_ctx->streams[video_stream_index]->time_base) * pkt.pts;
              qDebug()<<"video_time"<<video_clock;

              if(video_clock - time >= 2){
//                  av_packet_unref(&pkt);
                  pre_frame_internal_mutex.unlock();
                  break;
              }

            //解码视频 frame
            //发送视频帧
            if (avcodec_send_packet(decoder, &pkt) != 0)
            {
                av_packet_unref(&pkt);//不成功就释放这个pkt
                pre_frame_internal_mutex.unlock();
                continue;
            }
            //接受后对视频帧进行解码
            if (avcodec_receive_frame(decoder, SRC_VIDEO_pFrame) != 0)
            {
                av_packet_unref(&pkt);//不成功就释放这个pkt
                pre_frame_internal_mutex.unlock();
                continue;
            }
//            qDebug()<<"test point 1.2";

            //转格式
            sws_scale(img_convert_ctx,
                (uint8_t const **)
                      SRC_VIDEO_pFrame->data,
                SRC_VIDEO_pFrame->linesize, 0, video_height, RGB24_pFrame->data,
                RGB24_pFrame->linesize);

//            qDebug()<<"test point 1.5";

            //释放包
//            if()
//            for(int i = 0;i <100;i++);

//            av_packet_unref(&pkt);


//            qDebug()<<"test point 2";


//            pre_frame_mutex.lock();
            //加载图片数据
            QImage image(out_buffer_rgb, video_width, video_height, QImage::Format_RGB888);

            qDebug()<<"test point 3";


            struct IMAGE_FRAME_2 image_frame;
            image_frame.image = image;
            image_frame.video_clock = video_clock;
//            this->frame = image;

//            image.save("D:\\0.jpg");

//           pre_frame_mutex.unlock();
//          delete [] image.bits();


            //添加到队列
            frame_pack.append(image_frame);

//            qDebug()<<"test point 4";

            av_packet_unref(&pkt);

//            qDebug()<<"test point 6";

          }
        else{
//            qDebug()<<"time point 5";
             av_packet_unref(&pkt);
        }

        pre_frame_internal_mutex.unlock();

    }
    qDebug()<<"Len total"<<frame_pack.size();
    getClosetPacket(frame_pack);







////////////////////////////////////////////////

//        AVPacket packet;

//    //        pre_frame_mutex.lock();
//        int re = av_read_frame(pFormatCtx, &packet);
//        if(re != 0){
//            ;
//        }
//        else{
//        if(packet.stream_index == videoStream){
//            AVFrame *SRC_VIDEO_pFrame = av_frame_alloc();
//            AVFrame * RGB24_pFrame = av_frame_alloc();// 存放解码后YUV数据的缓冲区

//            //将解码后的YUV数据转换成RGB24
//            SwsContext *img_convert_ctx = sws_getContext(video_width, video_height,
//                format_ctx->streams[video_stream_index]->codec->pix_fmt, video_width, video_height,
//                AV_PIX_FMT_RGB24, SWS_BICUBIC, nullptr, nullptr, nullptr);

//            //计算RGB图像所占字节大小
//            int numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, video_width, video_height);

//            //申请空间存放RGB图像数据
//            uint8_t * out_buffer_rgb = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

//            // avpicture_fill函数将ptr指向的数据填充到picture内,但并没有拷贝,只是将picture结构内的data指针指向了ptr的数据
//            avpicture_fill((AVPicture *)RGB24_pFrame, out_buffer_rgb, AV_PIX_FMT_RGB24,
//                video_width, video_height);

//    //            packet_frame.packet_pointer = &packet;

//    //            qDebug()<<"timestamp"<<packet.pts*av_q2d(pFormatCtx->streams[packet.stream_index]->time_base);
//                res = avcodec_send_packet(pCodecCtx, &packet);
//                qDebug()<<"send完了";
//                if(res!=0){
//    //                av_packet_unref(&packet);
//    //                pre_frame_mutex.unlock();
//                    return;
//                }
//    //            qDebug()<<"res"<<res;
//                int gotPicture = avcodec_receive_frame(pCodecCtx, pFrameRGB); //gotPicture = 0 success, a frame was returned
//                qDebug()<<"gotPicture"<<gotPicture;
//                if(gotPicture == 0) {
//                    SwsContext* swsContext = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24,
//                                              SWS_BICUBIC, nullptr, nullptr, nullptr);
//                    if(swsContext == nullptr){
//                        return;
//                    }
//                    AVFrame* frameRGB = av_frame_alloc();
//                    avpicture_alloc((AVPicture*)frameRGB, AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
//                    int len1 = sws_scale(swsContext, pFrameRGB->data, pFrameRGB->linesize, 0, pCodecCtx->height, frameRGB->data, frameRGB->linesize);
//                    qDebug()<<"len1"<<len1;
//                    if(len1<0){
//                        av_packet_unref(&packet);
//                        avformat_close_input(&pFormatCtx);
//                        if(swsContext)
//                        sws_freeContext(swsContext);
//                        if(frameRGB)
//                        av_frame_unref(frameRGB);
//                        return;
//                    }
//                    QImage image(frameRGB->data[0], pCodecCtx->width, pCodecCtx->height, frameRGB->linesize[0], QImage::Format_RGB888);
//                    this->frame = image.copy();
//                    if(swsContext)
//                    sws_freeContext(swsContext);
//                    if(frameRGB)
//                    av_frame_unref(frameRGB);

//                }
//        }

//    }

//        av_packet_unref(&packet);
//        avformat_close_input(&pFormatCtx);
//        return;

//    }


//    QList<PACKET_FRAME> pack_frame_list;
////    qDebug()<<"线程运行";
//    AVFormatContext *pFormatCtx = avformat_alloc_context();
//    pFormatCtx->interrupt_callback.callback = interrupt_cb;

//    pFormatCtx->interrupt_callback.opaque = pFormatCtx;

////    AVDictionary* options = NULL;

////    av_dict_set(&options, "rtsp_transport", "tcp", 0);

//    int res;
//    std::string str = filename.toStdString();
//    const char* ch = str.c_str();
//    res = avformat_open_input(&pFormatCtx, ch, nullptr, nullptr);
//    if (res) {
//        qDebug()<<"打开上下文失败";
//        return;
//    }
//    avformat_find_stream_info(pFormatCtx, nullptr);
//    int videoStream = -1;
//    for(int i=0; i<pFormatCtx->nb_streams; i++) {
//        if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
//            videoStream=i;
//            break;
//        }
//    }
//    if(videoStream == -1) {
//        return;
//    }
//    AVCodecContext *pCodecCtxOrig = nullptr;
//    // Get a pointer to the codec context for the video stream
//    pCodecCtxOrig = pFormatCtx->streams[videoStream]->codec;
//    AVCodec *pCodec = nullptr;
//    // Find the decoder for the video stream
//    pCodec = avcodec_find_decoder(pCodecCtxOrig->codec_id);
//    if(pCodec == nullptr) {
//        fprintf(stderr, "Unsupported codec!\n");
//        return; // Codec not found
//    }

//    AVCodecContext *pCodecCtx = nullptr;
//    // Copy context
//    pCodecCtx = avcodec_alloc_context3(pCodec);
//    if(avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) {
//        fprintf(stderr, "Couldn't copy codec context");
//        return; // Error copying codec context
//    }
//    // Open codec
//    if(avcodec_open2(pCodecCtx, pCodec, nullptr)<0) {
//        return;// Could not open codec
//    }
//    AVFrame *pFrameRGB = nullptr;
//    pFrameRGB = av_frame_alloc();
////    qint64 current_frame_time = time - 5;

//    res = av_seek_frame(pFormatCtx, -1, (time-2) * AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);
//    if (res<0) {
//        return;
//    }



//    SwsContext* swsContext = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24,SWS_BICUBIC, nullptr, nullptr, nullptr);

//    while(1){


////        count = 0;
//        qDebug()<<"上锁，锁的数量为0";
////        pre_frame_mutex.lock();
//        qDebug()<<"Gangjin whilw";
//        AVPacket packet;

//        qDebug()<<"开始读";
//        callback1 = false;

////        m_pTimer->stop();
////        m_pTimer->start(100);
////        emit begintoread();
//        int flag = 0;
//        pre_frame_mutex.lock();

//        qDebug()<<"dushu";
//        int re = av_read_frame(pFormatCtx, &packet);
//        qDebug()<<"re"<<re;
//        qDebug()<<"读完了";
//        qDebug()<<"count=="<<count;
//        qDebug()<<"packet"<<packet.pts;

//        if(count >= 400){

//            qDebug()<<"在这骂";
//            count = 0;
////            pre_frame_mutex.unlock();
//            flag = 1;
//            pre_frame_mutex.unlock();
//            continue;
//        }
//        else{
//            flag = 1;
//            count = 0;

//            ;
//        }
//        pre_frame_mutex.unlock();
//        while(flag == 0);


//        if(re != 0){
//            av_packet_unref(&packet);
////            pre_frame_mutex.unlock();
//            qDebug()<<"去锁，锁的数量为1";
//            break;
//        }


//        qDebug()<<"wehile";
//        qDebug()<<"pts"<<av_q2d(pFormatCtx->streams[packet.stream_index]->time_base)-this->time;
//        if(packet.pts*av_q2d(pFormatCtx->streams[packet.stream_index]->time_base)-this->time>2){
//            av_packet_unref(&packet);
////            pre_frame_mutex.unlock();
//            qDebug()<<"去锁，锁的数量为1";
//            break;
////            return;
//            ;
//        }
//        qDebug()<<"在while中";
////        if(this->m_run == 2){
////            qDebug()<<"结束了";
////            frame = QImage();
//////            avformat_close_input(&pFormatCtx);
////            return;
////        }
////        av_read_frame(pFormatCtx, &packet);
////        qDebug()<<"r1"<<r1;
////        if(r1==0){
////        qDebug()<<"current_time"<<packet.pts*av_q2d(pFormatCtx->streams[packet.stream_index]->time_base);
//        if(packet.stream_index == videoStream){
//            qDebug()<<"okoklaile";

////            packet_frame.packet_pointer = &packet;

////            qDebug()<<"timestamp"<<packet.pts*av_q2d(pFormatCtx->streams[packet.stream_index]->time_base);
////            pre_frame_mutex.lock();
//            res = avcodec_send_packet(pCodecCtx, &packet);
//            qDebug()<<"send完了";
//            if(res!=0){
//                av_packet_unref(&packet);
////                pre_frame_mutex.unlock();
////                pre_frame_mutex.unlock();
//                qDebug()<<"去锁，锁的数量为1";
//                continue;
//            }
////            qDebug()<<"res"<<res;
//            int gotPicture = avcodec_receive_frame(pCodecCtx, pFrameRGB); //gotPicture = 0 success, a frame was returned
//            qDebug()<<"gotPicture"<<gotPicture;
//            if(gotPicture == 0) {
//                qDebug()<<"00000";

////                if(swsContext == nullptr){
////                    return;
////                }
//                qDebug()<<"test point2";
//                AVFrame* frameRGB = av_frame_alloc();
//                qDebug()<<"test point1";
//                avpicture_alloc((AVPicture*)frameRGB, AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
//                int len1 = sws_scale(swsContext, pFrameRGB->data, pFrameRGB->linesize, 0, pCodecCtx->height, frameRGB->data, frameRGB->linesize);
//                qDebug()<<"len1"<<len1;
//                if(len1<0){
//                    continue;
//                }
//                QImage image(frameRGB->data[0], pCodecCtx->width, pCodecCtx->height, frameRGB->linesize[0], QImage::Format_RGB888);
////                frame = image.copy();
//                qDebug()<<"是不是在这";
//                qDebug()<<"size1"<<image.size();
////                if(image.size().width() == 232){
////                    return;
////                }
//                PACKET_FRAME packet_frame;
//                packet_frame.packet_clock = packet.pts*av_q2d(pFormatCtx->streams[packet.stream_index]->time_base);
//                qDebug()<<"clock"<<packet_frame.packet_clock;
//                packet_frame.frame = image;
//                qDebug()<<"image.size"<<image.size();

//                pack_frame_list.append(packet_frame);
////                qDebug()<<"len"<<pack_frame_list.length();

////                image.save("D:\\0.jpg");
////                pre_frame_mutex.lock();
////                if(swsContext!=nullptr)

////                if(frameRGB)
////                    av_frame_unref(frameRGB);
////                pre_frame_mutex.unlock();
//                qDebug()<<"还能出俩吗";
//                av_frame_unref(frameRGB);
////                pre_frame_mutex.unlock();
//                qDebug()<<"去锁，锁的数量为1";

//            }

//            else{
//                av_packet_unref(&packet);
////                pre_frame_mutex.unlock();
//                qDebug()<<"去锁，锁的数量为1";
////                pre_frame_mutex.unlock();
//                continue;
//            }
////                av_packet_unref(&packet);
//        }

//        else{
//            av_packet_unref(&packet);
////            pre_frame_mutex.unlock();
//            qDebug()<<"去锁，锁的数量为1";
//            continue;
//        }
////        current_frame_time += 1;
////        qDebug()<<"回到循环头";
////        pre_frame_mutex.unlock();

//}

////    qDebug()<<"len"<<pack_frame_list.length();
////////////////////////////////////////////////
//    sws_freeContext(swsContext);
//    getClosetPacket(pack_frame_list);

//    avformat_close_input(&pFormatCtx);

//    return;


//        PACKET_FRAME closet_frame = getClosetPacket(frame_list);
//        packet_pointer = closet_frame.packet_pointer;
//        qDebug()<<"pts"<<packet_pointer->pts;

}

void PreviewFrame::run(){

    pre_frame_mutex.lock();
//    video_stream_index = -1;
    m_run = 1;
//    m_pTimer = new QTimer();
//    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(setCallBack()),Qt::DirectConnection);
//    this->m_run = 1;
//    this->reset();
    this->GetFutureFrame(this->time);
//    qDebug()<<"m_run"<<m_run;
//    if(m_run == 1){
    emit isDone(this->frame);
    pre_frame_mutex.unlock();
    qDebug()<<"preframe线程结束了";
//    }
//    else{
//        qDebug()<<"发出了";
//        emit notDone();
//    }
//    qDebug()<<"preframe结束了";
//    this->exec();

}


void PreviewFrame::getClosetPacket(QList<IMAGE_FRAME_2> &frame_pack){
//    qDebug()<<"谮麽回事";
//    for (int i = 0 ;i<packet_pointers.size();i++){
//        qDebug()<<"get_i"<<i;
//        qDebug()<<"clock"<<packet_pointers[i].packet_clock;
//        qDebug()<<"get_distance"<<getDistance(packet_pointers[i].packet_clock,this->time);
//    }

    double min = 1E10;
    qint64 min_index = -1;
    for(int i = 0 ;i<frame_pack.size();i++){
//        if(m_run == 2){
//            break;
//        }
//        qDebug()<<"this_time"<<this->time;
//        qDebug()<<"min"<<min;
//        qDebug()<<"min_index"<<min_index;
        if (getDistance(frame_pack[i].video_clock,this->time)<min){
            min = getDistance(frame_pack[i].video_clock,this->time);
            min_index = i;
//            qDebug()<<"clock"<<packet_pointers[i].packet_clock;

        }
    }
//    qDebug()<<"min_index"<<min_index;
    if (min_index != -1 && frame_pack.length()!=0){

        this->frame = frame_pack[min_index].image;
        qDebug()<<"final_clock"<<frame_pack[min_index].video_clock;
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
////    this->terminate();
//    this->m_run = 2;
//}

double PreviewFrame::getDistance(double a,double b){
    return a - b < 0? b - a : a- b;
}

void PreviewFrame::on_timer_timeout(){
//    qDebug()<<"Jieshu";
//    this->terminate();
//    m_ptimer->stop();

}


int PreviewFrame::interrupt_cb(void *ctx)
{
    qDebug()<<"Lail";
    count ++;
    qDebug()<<"count"<<count;
   if(count >= 400){
         qDebug()<<"okokfanhui";
         return 1;//这个就是超时的返回
   }
    return 0;
}

void PreviewFrame::setCallBack(){
//    qDebug()<<"毁掉了";
//    callback1 = true;
//    m_pTimer ->stop();
}

int PreviewFrame::is_keyframe_h264(AVPacket* pkt) {
// printf("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
// pkt->data[0], pkt->data[1], pkt->data[2], pkt->data[3], pkt->data[4],
// pkt->data[5], pkt->data[6], pkt->data[7], pkt->data[8], pkt->data[9]);
int length = 0;
unsigned char* p_buffer = pkt->data;
int i_buffer = pkt->size;
if ( (pkt->data[0] == 0 && pkt->data[1] == 0 && pkt->data[2] == 0 && pkt->data[3] == 1) ||
(pkt->data[0] == 0 && pkt->data[1] == 0 && pkt->data[2] == 1) ) {
while (i_buffer > 3) {
if (pkt->data[0] == 0 && pkt->data[1] == 0 && pkt->data[2] == 0 && pkt->data[3] == 1) {
p_buffer += 4;
i_buffer -= 4;
int nal_type = p_buffer[0] & 0x1f;
// printf("1 pkt.size %d length %d nal_type %d\n", pkt->size, length, nal_type);
if (nal_type == 5) return 1;
}
if (pkt->data[0] == 0 && pkt->data[1] == 0 && pkt->data[2] == 1) {
p_buffer += 3;
i_buffer -= 3;
int nal_type = p_buffer[0] & 0x1f;
// printf("2 pkt.size %d length %d nal_type %d\n", pkt->size, length, nal_type);
if (nal_type == 5) return 1;
}
p_buffer++;
i_buffer--;
}
} else {
while (i_buffer > 4) {
unsigned char* p = (unsigned char*)&length;
p[3] = p_buffer[0];
p[2] = p_buffer[1];
p[1] = p_buffer[2];
p[0] = p_buffer[3];
p_buffer += 4;
i_buffer -= 4;
int nal_type = p_buffer[0] & 0x1f;
//printf("3 p_buffer[0] 0x%02x pkt.size %d length %d nal_type %d\n", p_buffer[0], pkt->size, length, nal_type);
//if (nal_type == 5) return 1;
return 1;
p_buffer += length;
i_buffer -= length;
}
}
// printf("this h264 frame is not keyframe\n");
return 0;
}


int PreviewFrame::is_keyframe(AVCodec *dec, AVPacket* pkt) {
if (dec && dec->name) {
int cpylen = strlen((const char*)dec->name);
if (cpylen >= 4) {
if (0 == memcmp(dec->name, "h264", 4)) {
return is_keyframe_h264(pkt);
}
}
}
return 1;
}

