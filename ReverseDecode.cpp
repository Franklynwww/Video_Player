//#include "..\stdafx.h"
#include "ReverseDecode.h"
ReverseDecode::ReverseDecode()
{
    //注册解码器
    av_register_all();

    //清空队列
    video_pack.clear();

    qDebug() << "FFMPEG版本信息:" << av_version_info();
}

ReverseDecode::~ReverseDecode()
{
    FreeRAM();

//    if (vct) avcodec_close(vct);

    if (format_ctx)
    {

        avformat_close_input(&format_ctx);//释放解封装器的空间，以防空间被快速消耗完
        avformat_free_context(format_ctx);
    }
}

void ReverseDecode::FreeRAM()
{
//    qDebug()<<"freeram开始";
//    if(SRC_VIDEO_pFrame->data)av_freep(SRC_VIDEO_pFrame->data);
//    if(SRC_VIDEO_pFrame->buf)av_freep(SRC_VIDEO_pFrame->buf);
//    if(SRC_VIDEO_pFrame->extended_buf)av_freep(SRC_VIDEO_pFrame->extended_buf);
//    if(SRC_VIDEO_pFrame->extended_data)av_freep(SRC_VIDEO_pFrame->extended_data);
//    qDebug()<<"freeram开始1";

    if (img_convert_ctx)sws_freeContext(img_convert_ctx);
//    qDebug()<<"freeram开始4";
    if (SRC_VIDEO_pFrame) av_frame_free(&SRC_VIDEO_pFrame);
//    qDebug()<<"freeram开始2";
    if (RGB24_pFrame) av_frame_free(&RGB24_pFrame);
//    qDebug()<<"freeram开始3";
    if (out_buffer_rgb)av_free(out_buffer_rgb);
//    qDebug()<<"freeram开始5";


    SRC_VIDEO_pFrame = nullptr;
    RGB24_pFrame = nullptr;
    img_convert_ctx = nullptr;
    out_buffer_rgb = nullptr;

    video_stream_index = -1;

//    qDebug()<<"freeram结束";

}


/*
工程: FFMPE_ReversePlay
日期: 2021-04-06
作者: DS小龙哥
环境: win10 QT5.12.6 MinGW32
功能: 加载媒体文件
*/
int ReverseDecode::LoadVideoFile(QString media)
{
    qDebug()<<"load开始";
    //释放空间
    FreeRAM();
    strncpy(m_MediaFile, media.toUtf8().data(), sizeof(m_MediaFile));

    QFileInfo info(media);

    //得到后缀
    file_suffix=info.suffix();
    qDebug()<<"file_suffix:"<<file_suffix;

    //分配上下文
    format_ctx = avformat_alloc_context();
    if (avformat_open_input(&format_ctx, m_MediaFile, nullptr, nullptr) != 0)
    {
        LogSend(tr("无法打开视频文件: %1").arg(m_MediaFile));
        return -1;
    }


    //读取媒体文件的数据包以获取流信息
    if (avformat_find_stream_info(format_ctx, nullptr) < 0)
    {
        LogSend(tr("无法获取流信息.\n"));
        return -1;
    }

    LogSend(tr("视频中流的数量: %1\n").arg(format_ctx->nb_streams));
    for (int i = 0; i < format_ctx->nb_streams; ++i)
    {
        const AVStream* stream = format_ctx->streams[i];
        if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            //查找解码器
            AVCodec *video_pCodec = avcodec_find_decoder(stream->codecpar->codec_id);

            vct = avcodec_alloc_context3(video_pCodec);
            avcodec_parameters_to_context(vct, stream->codecpar);

            //打开解码器
//            if (avcodec_open2(stream->codec, video_pCodec, nullptr) != 0)
//            {
//                LogSend(tr("解码器打开失败.\n"));
//                return -1;
//            }
            if (avcodec_open2(vct, video_pCodec, nullptr) != 0)
            {
                LogSend(tr("解码器打开失败.\n"));
                return -1;
            }

            video_stream_index = i;
            //得到视频帧的宽高
            video_width = stream->codecpar->width;
            video_height = stream->codecpar->height;

            LogSend(tr("视频帧的尺寸(以像素为单位): (宽X高)%1x%2 像素格式: %3\n").arg(
                stream->codecpar->width).arg(stream->codecpar->height).arg(stream->codecpar->format));

        }
    }

    qDebug()<<"test point111111";
    qDebug()<<"video_stream_index"<<video_stream_index;
    if (video_stream_index == -1)
    {
        qDebug()<<("没有检测到视频流.\n");
        emit noVideo();
        return 1;
    }

    qDebug()<<"222222";
    for (int i = 0; i < format_ctx->nb_streams; ++i)
    {
        const AVStream* stream = format_ctx->streams[i];
//        if (stream->codec->codec_type == AVMEDIA_TYPE_AUDIO)
//        {
//            //查找解码器
//            AVCodec *audio_pCodec = avcodec_find_decoder(stream->codecpar->codec_id);
//            //打开解码器
//            if (avcodec_open2(stream->codec, audio_pCodec, nullptr) != 0)
//            {
//                LogSend(tr("解码器打开失败.\n"));
//                return -1;
//            }
//            audio_stream_index = i;
////            sampleRate = stream->codecpar->sample_rate;
////            channels = stream->codecpar->channels;
////            stream->codec->channel_layout = av_get_default_channel_layout(stream->codec->channels);


//            out_channel_layout = stream->codecpar->channel_layout;
//            out_sample_fmt = AV_SAMPLE_FMT_S16;
//            out_sample_rate = stream->codecpar->sample_rate;
//            out_channels = av_get_channel_layout_nb_channels(out_channel_layout);




////            video_width = stream->codecpar->width;
////            video_height = stream->codecpar->height;

//            LogSend(tr("音频帧的采样率%1 频道: %2\n").arg(
//                stream->codecpar->sample_rate).arg(stream->codecpar->channels));
//        }

    }

//    if (audio_stream_index == -1)
//    {
//        LogSend("没有检测到音频流.\n");
//        return -1;
//    }

    AVRational frameRate = format_ctx->streams[video_stream_index]->avg_frame_rate;
//    AVRational frameRate = format_ctx->streams[video_stream_index]->avg_frame_rate;

    qDebug()<<"framerate"<<frameRate.den;

    /*设置视频转码器*/
    SRC_VIDEO_pFrame = av_frame_alloc();
    RGB24_pFrame = av_frame_alloc();// 存放解码后YUV数据的缓冲区

    //将解码后的YUV数据转换成RGB24
    img_convert_ctx = sws_getContext(video_width, video_height,
        vct->pix_fmt, video_width, video_height,
        AV_PIX_FMT_RGB24, SWS_BICUBIC, nullptr, nullptr, nullptr);

    qDebug()<<"Henkeneng";
    //计算RGB图像所占字节大小
    int numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, video_width, video_height);

    qDebug()<<"buffer size(B)"<<numBytes;
    //申请空间存放RGB图像数据
    out_buffer_rgb = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

    // avpicture_fill函数将ptr指向的数据填充到picture内,但并没有拷贝,只是将picture结构内的data指针指向了ptr的数据
    avpicture_fill((AVPicture *)RGB24_pFrame, out_buffer_rgb, AV_PIX_FMT_RGB24,
        video_width, video_height);

    //申请空间存放重采样后的音频数据
//    out_buffer_audio = (uint8_t *)av_malloc(MAX_AUDIO_FRAME_SIZE*2);


    over_pack.clear();
    video_pack.clear();
//    audio_pack.clear();

    //每当加载新媒体的时候这间隔时间就清0
    m_DifferTime = DEFAULT_DIFFER_TIME;

    //初始值给视频的最大值
    m_oldPosMs = format_ctx->duration;

    qDebug()<<"old_pos"<<m_oldPosMs;

    return 0;
}


void ReverseDecode::SetSate(int run)
{
    m_run = run;
}

int ReverseDecode::GetSate()
{
    return m_run;
}


//跳转视频帧  传入的pos是毫秒单位
void ReverseDecode::SetSeekPos(qint64 pos)
{
    //初始值给视频的最大值
    m_oldPosMs = format_ctx->duration;
    is_CurrentSeekPos = 1;
    m_seek=m_n64CurrentSeekPos = pos / 1000.0;  //变成秒单位
//    video_pack.clear();
    over_pack.clear();
//    over_pack2.clear();
    qDebug() << "**************倒放解码:SetSeekPos**************:" << pos << "," << m_seek;
}


void ReverseDecode::PausePlay()
{
    qDebug() << "**************倒放解码:PausePlay**************";
    emit ss_ReversePlayFinish();
    m_run = 2;
}

void ReverseDecode::StopPlay()
{
    qDebug() << "**************倒放解码:StopPlay**************";
//    emit ss_ReversePlayFinish();
    m_run = 0;
}

void ReverseDecode::LogSend(QString text)
{
    qDebug() << text;
}

qint64 ReverseDecode::GetDuration()
{
    //format_ctx->duration *1.0 / AV_TIME_BASE  //得到秒
    return format_ctx->duration / 1000;  //得到毫秒
}

//线程执行起点
void ReverseDecode::run()
{
    emit started();
    this->want_to_finished = false;
    this->finished = false;
    video_pack.clear();
    over_pack.clear();
    this->sleeptime = 0;
    this->video_tolerence = 0;

    LogSend("开始播放视频.\n");
    StartPlay();
    qDebug()<<"完全结束了";
    this->finished = true;
    emit isDone();

}

//解码数据包
int ReverseDecode::DecodDataPack()
{
    qDebug()<<"size of video_pack"<<video_pack.size();


    //判断上次是否还有没有播放完的包
    if (over_pack.size() > 0)
    {

//        qDebug()<<"xieededifang";
        for (int i = 0; i < over_pack.size(); i++)
        {

            video_pack.append(over_pack.at(i));
        }
    }

    if(video_pack.size() == 0){
        qDebug()<<"搜狐";
        video_tolerence++;
        if(video_tolerence>=200){
        this->want_to_finished = true;
        }
        return 1;
    }
    else{
        video_tolerence = 0;
    }


    if (video_pack.size() >= 2)
    {
        //如果等于默认时间
//        if (m_DifferTime == DEFAULT_DIFFER_TIME)
//        {
//            //计算间隔时间
//            qint32 m_tmp = (video_pack.at(3).video_clock - video_pack.at(2).video_clock) * 1000;
//            if(m_tmp>0)
//            {
//                //重新更新间隔时间
//                m_DifferTime =m_tmp;
//                qDebug() << "两帧相差的时间:" << m_DifferTime;
//            }
//        }
    }

    if (video_pack.size() > 0)
    {
//        for(int i =0 ;i<video_pack.size();i++){
//            qDebug()<<"video_pack["<<i<<"].clock"<<video_pack[i].video_clock;
//        }
        int i = 0;
        int cnt_i=1;
//        if(file_suffix=="mpg")cnt_i=8;
        for (i = video_pack.size() - 1; i > cnt_i; i--)
        {
            //时间信号-秒转为毫秒
            if (m_DifferTime == DEFAULT_DIFFER_TIME)
            {
                //计算间隔时间
                qint32 m_tmp = (video_pack.at(i).video_clock - video_pack.at(i-1).video_clock) * 1000;
                if(m_tmp>0)
                {
                    //重新更新间隔时间
                    m_DifferTime =m_tmp;
                    qDebug() << "两帧相差的时间video:" << m_DifferTime;
                }
            }

            qint64 pos_ms = video_pack.at(i).video_clock * 1000;
//            qDebug()<<"ori_video_pos"<<pos_ms;

            if(pos_ms < 0){
                continue;
            }
            //因为是倒放.下一帧的时间肯定要比上一帧小,如果大于说明帧有问题不能显示
            if (pos_ms<m_oldPosMs)
            {
                m_oldPosMs = pos_ms;


//                qDebug()<<"audio_time"<<audio_time;
//                qDebug()<<"video_time"<<video_time;
                //通知界面更新
//                if(audio_time - video_time > 3){
//                    qDebug()<<"vedio要休眠一下";
//                    msleep(3000);
//                }
                qDebug()<<"video_pos"<<video_pack.at(i).video_clock;
                emit SendOneFrame(video_pack.at(i).image.copy(),video_pack.at(i).video_clock);
//                qDebug()<<"pos_before_emit"<<pos_ms<<"m_run"<<m_run;
                if(video_pack.at(i).video_clock < 1){
                    this->want_to_finished = true;
                    qDebug()<<"快完了我";
                }
                //更新时间

//                emit positionChanged1(pos_ms);
                //同步画面,看起来差不多
                //QThread::msleep(40);
//                qDebug()<<"differ time"<<m_DifferTime;
                QThread::msleep(m_DifferTime);
                sleeptime = 0;

                //int delay_time_cnt = 0;
                //while (true)
                //{
                //	if (m_run != 1)break;//如果状态不是运行状态
                //	delay_time_cnt++;
                //	QThread::msleep(1);
                //	if (delay_time_cnt >= m_DifferTime/2)break; //时间到达
                //}
            }
            //qDebug() << "m_oldPosMs:" << m_oldPosMs<<"_pos_ms:"<< pos_ms;

            //如果状态不是运行状态
            if (m_run != 1)
            {
                break;
            }
        }

        if (i != 0 && m_run != 1)
        {   over_pack.clear();
            qDebug()<<"end i"<<i;
            //保存没有播放完的包
//            if(m_run!=1){
            for (int j = 0; j < i; j++)
            {
                over_pack.append(video_pack.at(j));
            }
//            }
        }
        video_pack.clear();

        //判断是否是因为需要跳转才退出循环的
        if (is_CurrentSeekPos)
        {
            video_pack.clear();
            over_pack.clear();
        }
    }
    return 0;
}


int ReverseDecode::DecodDataPack2(){
//    qDebug()<<"进入datapack2";
//    //判断上次是否还有没有播放完的包
//    if (over_pack2.size() > 0)
//    {
//        for (int i = 0; i < over_pack2.size(); i++)
//        {
//            audio_pack.append(over_pack2.at(i));
//        }
//    }

//    if (audio_pack.size() >= 2)
//    {
//        //如果等于默认时间
//        if (m_DifferTime == DEFAULT_DIFFER_TIME)
//        {
//            //计算间隔时间
//            qint32 m_tmp = (audio_pack.at(1).audio_clock - audio_pack.at(0).audio_clock) * 1000;
//            if(m_tmp>0)
//            {
//                //重新更新间隔时间
//                m_DifferTime =m_tmp;
//                qDebug() << "两帧相差的时间:" << m_DifferTime;
//            }
//        }
//    }

//    if (audio_pack.size() > 0)
//    {
//        qDebug()<<"zaine";
//        int i = 0;
//        int cnt_i=1;
////        if(file_suffix=="mpg")cnt_i=8;
//        for (i = audio_pack.size() - 1; i > cnt_i; i--)
//        {
//            //时间信号-秒转为毫秒
//            qint64 pos_ms = audio_pack.at(i).audio_clock * 1000;

//            //因为是倒放.下一帧的时间肯定要比上一帧小,如果大于说明帧有问题不能显示
//            if (pos_ms<m_oldPosMs)
//            {
//                //通知界面更新
//                emit SendOneFrame(QImage(),audio_pack.at(i).audio,1);


//                qDebug()<<"pos"<<pos_ms;

//                //更新时间
//                m_oldPosMs = pos_ms;
//                emit positionChanged1(pos_ms);
//                //同步画面,看起来差不多
//                //QThread::msleep(40);
//                QThread::msleep(m_DifferTime);

//                //int delay_time_cnt = 0;
//                //while (true)
//                //{
//                //	if (m_run != 1)break;//如果状态不是运行状态
//                //	delay_time_cnt++;
//                //	QThread::msleep(1);
//                //	if (delay_time_cnt >= m_DifferTime/2)break; //时间到达
//                //}
//            }
//            //qDebug() << "m_oldPosMs:" << m_oldPosMs<<"_pos_ms:"<< pos_ms;

//            //如果状态不是运行状态
//            if (m_run != 1)
//            {
//                break;
//            }
//        }
//        if (i != 0)
//        {
//            over_pack2.clear();
//            //保存没有播放完的包
//            for (int j = 0; j <= i; j++)
//            {
//                over_pack2.append(audio_pack.at(j));
//            }
//        }
//        audio_pack.clear();

//        //判断是否是因为需要跳转才退出循环的
//        if (is_CurrentSeekPos)
//        {
//            audio_pack.clear();
//            over_pack2.clear();
//        }
//    }
//    return 0;
}

//播放视频
int ReverseDecode::StartPlay()
{

    ////默认从视频结尾开始播放
    //m_n64CurrentSeekPos=format_ctx->duration *1.0 / AV_TIME_BASE;

    //m_endSeekPos=m_n64CurrentSeekPos;
    ////向后偏移2秒
    //m_n64CurrentSeekPos-=2;
    ////偏移到指定位置再开始解码    AVSEEK_FLAG_BACKWARD 向后找最近的关键帧
    //av_seek_frame(format_ctx, -1, m_n64CurrentSeekPos* AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);
    //seek_state=1;

    //表示视频加载成功
    while (m_run)
    {
//        qDebug()<<"finished"<<finished;
        if(want_to_finished == true){
//            finished = true;
            finished = true;
            return 1;
        }
//        qDebug()<<"m_run_in_video"<<m_run;
        if (m_run == 2)
        {
            // qDebug()<<"暂停状态.";
//            msleep(100); //暂停播放
            continue;
        }

        if (is_CurrentSeekPos)
        {
            is_CurrentSeekPos = 0;


            //向后偏移1秒
            m_endSeekPos = m_seek;

            int64_t seek_val = m_seek * AV_TIME_BASE;

            //偏移到指定位置再开始解码    AVSEEK_FLAG_BACKWARD 向后找最近的关键帧
            av_seek_frame(format_ctx, -1, seek_val, AVSEEK_FLAG_BACKWARD);

            seek_state = 1;
            //清空队列
            video_pack.clear();
            over_pack.clear();
//            audio_pack.clear();
//            over_pack2.clear();
            qDebug() << "外部触发seek:" << seek_val<<",m_seek:"<< m_seek;
        }

        double video_clock;
        double audio_clock;
        AVPacket pkt;

        //读取一帧数据
        if (av_read_frame(format_ctx, &pkt) < 0)
        {
            //m_run = 2; //设置为暂停状态
            //解码数据包
            qDebug()<<"从1入口进去";
            DecodDataPack();

            m_endSeekPos = m_n64CurrentSeekPos;

            //向后偏移1秒
            m_n64CurrentSeekPos -= 1;
            //偏移到指定位置再开始解码    AVSEEK_FLAG_BACKWARD 向后找最近的关键帧
            if(m_n64CurrentSeekPos <= -1){
                this->want_to_finished = true;
            }
            qint64 seek_val = m_n64CurrentSeekPos * AV_TIME_BASE;
            av_seek_frame(format_ctx, -1, seek_val, AVSEEK_FLAG_BACKWARD);
            seek_state = 1;

            //qDebug() << "完成一段解码.";
          //  QThread::sleep(5);
            qDebug() << "video数据读取完毕.";
//            av_packet_unref(&pkt);
            continue;
        }

        if (pkt.stream_index == video_stream_index)
        {
//            qDebug()<<"在解码了";
//            qDebug()<<video_pack.size();

            //当前时间
            video_clock = av_q2d(format_ctx->streams[video_stream_index]->time_base) * pkt.pts;
            qDebug()<<"video_time"<<video_clock;

            //说明之前偏移过
            if (seek_state)
            {
                m_n64CurrentSeekPos = video_clock;
                seek_state = 0;
            }

            //解码视频 frame
            //发送视频帧
            if (avcodec_send_packet(vct, &pkt) != 0)
            {
                av_packet_unref(&pkt);//不成功就释放这个pkt
                continue;
            }
            //接受后对视频帧进行解码
            if (avcodec_receive_frame(vct, SRC_VIDEO_pFrame) != 0)
            {
                av_packet_unref(&pkt);//不成功就释放这个pkt
                continue;
            }

            //转格式
            sws_scale(img_convert_ctx,
                (uint8_t const **)
                      SRC_VIDEO_pFrame->data,
                SRC_VIDEO_pFrame->linesize, 0, video_height, RGB24_pFrame->data,
                RGB24_pFrame->linesize);

            //释放包

            qDebug()<<"m_endSeekPos_image"<<m_endSeekPos;

            //加载图片数据
            QImage image(out_buffer_rgb, video_width, video_height, QImage::Format_RGB888);

            struct IMAGE_FRAME image_frame;
            image_frame.image = image.copy();
            image_frame.video_clock = video_clock;

            //添加到队列
            video_pack.append(image_frame);

            //解码到结尾
            if (video_clock >= m_endSeekPos+1)
            {
                qDebug()<<"满足条件的video_clock"<<video_clock;
                //读取到最开头的一帧数据
                qDebug()<<"满足条件的m_endSeekPos+1"<<m_endSeekPos+1;
                //读取到最开头的一帧数据
                if (video_pack.size() == 1)
                {
                    if (video_pack.at(0).video_clock <= 1.5)
                    {
                        qDebug() << "读取到最开头的一帧数据:" << video_pack.at(0).video_clock;
                        //解码数据包
                        qDebug()<<"从2入口进去";
                        DecodDataPack();
                        m_run = 2; //设置为暂停状态
                        continue; //回到循环头继续
                    }
                }

                //解码数据包
                qDebug()<<"从3入口进去";
                DecodDataPack();

                m_endSeekPos = m_n64CurrentSeekPos;

                //向后偏移10秒
                m_n64CurrentSeekPos -= 5;
                qDebug()<<"m_n64CurrentSeekPos"<<m_n64CurrentSeekPos;
                //偏移到指定位置再开始解码    AVSEEK_FLAG_BACKWARD 向后找最近的关键帧

                if(m_n64CurrentSeekPos <= -5){
                    this->want_to_finished = true;
                }

                qint64 seek_val = m_n64CurrentSeekPos * AV_TIME_BASE;
                av_seek_frame(format_ctx, -1, seek_val, AVSEEK_FLAG_BACKWARD);
                seek_state = 1;

//                qDebug() << "完成一段解码.pos为"<<m_n64CurrentSeekPos;
              //  QThread::sleep(5);
                qDebug()<<"finished"<<this->finished;
                if(this->finished == true){
                    qDebug()<<"该结束了";
                    return 0;
            }

            }
//            av_packet_unref(&pkt);
        }

//        if (pkt.stream_index == audio_stream_index)
//        {
//            qDebug()<<"在解码音频了";
////            qDebug()<<audio_pack.size();

//            //当前时间
//            audio_clock = av_q2d(format_ctx->streams[audio_stream_index]->time_base) * pkt.pts;
//            qDebug()<<"audio_time"<<audio_clock;

//            //说明之前偏移过
//            if (seek_state)
//            {
//                m_n64CurrentSeekPos = audio_clock;
//                seek_state = 0;
//            }

//            //解码音频 frame
//            //发送音频帧
//            if (avcodec_send_packet(format_ctx->streams[audio_stream_index]->codec, &pkt) != 0)
//            {
//                av_packet_unref(&pkt);//不成功就释放这个pkt
//                qDebug()<<"不v恒功se";
//                continue;
//            }
//            //接受后对视频帧进行解码
//            if (avcodec_receive_frame(format_ctx->streams[audio_stream_index]->codec, SRC_VIDEO_pFrame) != 0)
//            {
//                av_packet_unref(&pkt);//不成功就释放这个pkt
//                qDebug()<<"不v恒功recv";
//                continue;
//            }

//            SwrContext *swr_ctx = swr_alloc_set_opts(NULL, out_channel_layout, out_sample_fmt,out_sample_rate, format_ctx->streams[audio_stream_index]->codec->channel_layout, format_ctx->streams[audio_stream_index]->codec->sample_fmt, format_ctx->streams[audio_stream_index]->codec->sample_rate, 0, 0);
//            swr_init(swr_ctx);

//            //转格式
//            int len = swr_convert(swr_ctx, &out_buffer_audio, MAX_AUDIO_FRAME_SIZE*2, (const uint8_t **)SRC_VIDEO_pFrame->data, SRC_VIDEO_pFrame->nb_samples);
//            if (len <= 0)
//            {
//                qDebug()<<"转音频格式出错";
//                continue;
//            }
//            qDebug()<<"转音频成功，结果为len=="<<len;
//            int dst_bufsize = av_samples_get_buffer_size(0, out_channels, len, out_sample_fmt, 1);
//            QByteArray atemp =  QByteArray((const char *)out_buffer_audio, dst_bufsize);




//            struct AUDIO_FRAME audio_frame;
//            audio_frame.audio = atemp;
//            audio_frame.audio_clock = audio_clock;

//            //添加到队列
//            audio_pack.append(audio_frame);
//            qDebug()<<"audio_pack.size()=="<<audio_pack.size();



//            //释放包
//            av_packet_unref(&pkt);
//            qDebug()<<"m_endSeekPos_audio"<<m_endSeekPos;

//            //解码到结尾
//            if (audio_clock >= m_endSeekPos+1)
//            {
//                //读取到最开头的一帧数据
//                if (audio_pack.size() == 1)
//                {
//                    if (audio_pack.at(0).audio_clock <= 1.5)
//                    {
//                        qDebug() << "读取到最开头的一帧数据:" << video_pack.at(0).video_clock;
//                        //解码数据包
//                        DecodDataPack2();
//                        m_run = 2; //设置为暂停状态
//                        continue; //回到循环头继续
//                    }
//                }

//                qDebug()<<"解码前"<<m_endSeekPos;
//                //解码数据包
//                DecodDataPack2();

//                m_endSeekPos = m_n64CurrentSeekPos;

//                //向后偏移10秒
//                m_n64CurrentSeekPos -= 5;
//                //偏移到指定位置再开始解码    AVSEEK_FLAG_BACKWARD 向后找最近的关键帧

//                qint64 seek_val = m_n64CurrentSeekPos * AV_TIME_BASE;
//                av_seek_frame(format_ctx, -1, seek_val, AVSEEK_FLAG_BACKWARD);
//                seek_state = 1;

//                qDebug() << "完成一段音频的解码.";
//              //  QThread::sleep(5);
//            }
//            if(this->finished == true){
//                qDebug()<<"该结束了";
//                return 0;
//        }
//        }


    }

    LogSend("视频音频解码播放器的线程退出成功.\n");
    return 0;
}


void ReverseDecode::finish(){
//    this->finished = true;
}
