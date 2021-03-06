#include "utils.h"
bool isValidVideoFile(QString filename){
    filename = filename.toLower();
    int lastindex = filename.lastIndexOf(".");
    QString type = "";
    for (int i = lastindex+1;i<filename.length();i++){
        type += filename[i];
    }
    if (type == "avi" || type == "wmv" || type == "mpg" || type == "mpeg" || type == "rm"
            || type == "ram"  || type == "flv" || type == "mp4" || type == "mp3" || type == "wma"
            || type == "rmvb" || type == "mkv" || type == "wav"){
        return true;
    }
    return false;
}

bool isVideoOrAudio(QString filename){
    filename = filename.toLower();
    int lastindex = filename.lastIndexOf(".");
    QString type = "";
    for (int i = lastindex+1;i<filename.length();i++){
        type += filename[i];
    }
    if (type == "avi" || type == "wmv" || type == "mpg" || type == "mpeg" || type == "mov" || type == "rm"
            || type == "ram" || type == "swf" || type == "flv" || type == "mp4" ){
        return VIDEO;
    }
    else{
        return AUDIO;
    }
}

QString transfer_to_std_time(qint64 miniseconds){
    QString res = "";
    qint64 second = miniseconds / 1000;
    int hours = second / 3600;
    int minutes = (second - hours * 3600)/60;
    int seconds = second - hours * 3600 - minutes * 60;
    QString hours_str =  QString::number(hours, 10);
    if (hours_str.length() < 2){
        hours_str.insert(0,"0");
    }
    QString minutes_str =  QString::number(minutes, 10);
    if (minutes_str.length() < 2){
        minutes_str.insert(0,"0");
    }
    QString seconds_str =  QString::number(seconds, 10);
    if (seconds_str.length() < 2){
        seconds_str.insert(0,"0");
    }
    res = hours_str + ":" + minutes_str+ ":" +seconds_str;
    return res;


}

void pngTomp4_2()         //png图集转mp4
{
//    QString folder_path = "D:\\images\\";
//    if(folder_path.isEmpty())   return;


//    QString outFilename = "D:\\01.mp4";
//    if(outFilename.isEmpty())   return;

////    QStringList filters;
////    filters<<QString("*.png");

////    定义迭代器并设置过滤器
////    QDirIterator dir_iterator(folder_path,filters, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
////    QList<QString > pnglist;
////    while(dir_iterator.hasNext())       //获取目录下的png文件
////    {
////        dir_iterator.next();
////        QFileInfo file_info = dir_iterator.fileInfo();
////        pnglist.append(QString(tr("%1").arg(file_info.absoluteFilePath())));
////    }


//    AVFormatContext *kAVFormatContext;
//    AVOutputFormat *kAVOutputFormat;
//    AVCodecContext *kAVCodecContext;
//    AVDictionary *kAVDictionary = NULL;
//    AVDictionary *opt = NULL;
//    AVCodec *video_codec;
//    AVStream *kAVStream;
//    AVFrame *frame;
//    AVFrame *tmp_frame;
//    AVPacket kAVPacket = { 0 };
//    struct SwsContext *kSwsContext;
//    AVRational time{1,24};  /*1s25帧*/
//    AVRational time_1{1,1};  /*1s25帧*/
//    uint8_t *intBuffer = 0;                           // 图片数据缓冲区

//    int ret;
//    int got_packer = 0;
//    int64_t next_pts = 0;

//    tmp_frame = av_frame_alloc();
//    av_init_packet(&kAVPacket);

//    av_register_all();     //1、注册所有容易和编解码器

//    /* 2、分配输出媒体上下文 */
//    avformat_alloc_output_context2(&kAVFormatContext, NULL, NULL, outFilename.toLocal8Bit().data());      //上下文结构体、输出结构体、文件类型、路径

//    if(!kAVFormatContext)        //如果根据文件名没有找到对应的格式则默认mpeg格式
//    {
//        ret = avformat_alloc_output_context2(&kAVFormatContext, NULL, "mpeg",  outFilename.toLocal8Bit().data());    //没有找到文件类型默认mpeg（MP4）
//    }
//    if(!kAVOutputFormat) { goto end;}

//    kAVOutputFormat = kAVFormatContext->oformat;    //把输出操作结构体赋值出来

//    if (!(kAVOutputFormat->flags & AVFMT_NOFILE))   /* 如果需要，打开输出文件*/
//    {
//        ret = avio_open(&kAVFormatContext->pb, outFilename.toLocal8Bit().data(), AVIO_FLAG_WRITE);  //3、打开输出文件
//        if (ret < 0) {qDebug()<<"打开输出文件失败。"<<ret; }
//    }

//    /* 使用默认格式的编解码器添加音频和视频流，并初始化编解码器。*/
//    if (kAVOutputFormat->video_codec != AV_CODEC_ID_NONE)
//    {
//        video_codec = avcodec_find_encoder(kAVOutputFormat->video_codec);   //4、找到编码器
//        if(!video_codec)    goto end;

//        kAVStream = avformat_new_stream(kAVFormatContext,NULL);         //5、新建一个输出流
//        if(!kAVStream) {qDebug()<<"创建流kAVStream失败。";goto end;}

//        kAVCodecContext = avcodec_alloc_context3(video_codec);      //初始化一个AVCodecContext
//        if(!kAVCodecContext)    {qDebug()<<"用编码器video_codec初始化的kAVCodecContext默认参数失败";goto end;}

//        switch(video_codec->type)
//        {
//        case AVMEDIA_TYPE_VIDEO:

//            kAVCodecContext->codec_id = video_codec->id;
//            kAVCodecContext->bit_rate = 800000;
//            kAVCodecContext->width = 720;
//            kAVCodecContext->height = 404;
//            kAVStream->time_base = time;
//            kAVCodecContext->time_base = time;
//            kAVCodecContext->gop_size = 12; /*最多每十二帧发射一个内帧 */
//            kAVCodecContext->pix_fmt = AV_PIX_FMT_YUV420P;
//            if (kAVCodecContext->codec_id == AV_CODEC_ID_MPEG2VIDEO)
//            {
//                kAVCodecContext->max_b_frames = 2;  /*为了测试，我们还添加了b帧*/
//            }
//            if (kAVCodecContext->codec_id == AV_CODEC_ID_MPEG1VIDEO)
//            {
//                /* 需要避免使用一些coeffs溢出的宏块。这在正常的视频中不会发生，
//                 * 只是在色度平面的运动与luma平面不匹配时才会发生。 */
//                kAVCodecContext->mb_decision = 2;
//            }

//            break;
//        case AVMEDIA_TYPE_AUDIO:
//            break;

//        default:
//            break;
//        }

//        if(kAVOutputFormat->flags & AVFMT_GLOBALHEADER)/*有些格式希望流标头是单独的*/
//        {
//            kAVCodecContext->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;
//        }
//    }

//    av_dict_copy(&opt,kAVDictionary, 0);
//    ret = avcodec_open2(kAVCodecContext,video_codec,&opt);      //6、打开编码器
//    if(ret<0){qDebug()<<"打开视频编解码器失败"<<ret; goto end;}
//    av_dict_free(&opt);

//    frame = av_frame_alloc();
//    if(!frame)  {qDebug()<<"分配帧失败."; goto end;}
//    frame->format = kAVCodecContext->pix_fmt;
//    frame->width = kAVCodecContext->width;
//    frame->height = kAVCodecContext->height;

//    ret = av_frame_get_buffer(frame, 32);   //分配内存空间frame必须要有上三条件，32也就是4字节对齐
//    if(ret < 0){qDebug()<<"frame分配内存失败"; goto end;}

//    ret = avcodec_parameters_from_context(kAVStream->codecpar,kAVCodecContext);/*将流参数复制到muxer */
//    if (ret < 0) {qDebug()<<"无法复制流参数";goto end; }

//    av_dump_format(kAVFormatContext, 0, outFilename.toLocal8Bit().data(), 1);     //打印输出文件的详细信息



//    ret = avformat_write_header(kAVFormatContext,&kAVDictionary);/* 7、写流标头(如果有的话)*/
//    if(ret < 0){qDebug()<<"写流标题失败"; goto end;}


//    //8、写入每一帧数据
//    for(int i = 0; i<527; i++)
//    {
////        if(av_compare_ts(next_pts, kAVCodecContext->time_base,  10.0, time_1) > 0)      /*这里只生成10s的视频*/
////        {
////            qDebug()<<"暂时不需要生成新的帧"; break;
////        }
//        if (av_frame_make_writable(frame) < 0)  {goto end;}  /*当我们传递一个帧给编码器时，它可能会在内部保留一个对它的引用;确保我们没有在这里覆盖它*/

//        QImage img(tr("%1/%2.png").arg(folder_path).arg(i));
//        if(img.isNull()){qDebug()<<"打开图片失败";break;}
//        img = img.convertToFormat(QImage::Format_RGB888);

//        kSwsContext = sws_getContext(kAVCodecContext->width,kAVCodecContext->height,
//                                     AV_PIX_FMT_RGB24,kAVCodecContext->width,kAVCodecContext->height,
//                                     AV_PIX_FMT_YUV420P,SWS_LANCZOS | SWS_ACCURATE_RND,NULL,NULL,NULL);
//        if(!kSwsContext){qDebug()<<"无法初始化图片转换器";    goto end;}


//        intBuffer = (uint8_t*)malloc(sizeof(uint8_t)*img.bytesPerLine()*img.height());
//        memcpy(intBuffer,img.constBits(),sizeof(uint8_t)*img.bytesPerLine()*img.height());
//        avpicture_fill((AVPicture *)tmp_frame,intBuffer,AV_PIX_FMT_RGB24,kAVCodecContext->width,kAVCodecContext->height); //pAVFrame32的data指针指向了outBuffer

//        sws_scale(kSwsContext,(const uint8_t * const *)tmp_frame->data,
//                  tmp_frame->linesize,0,kAVCodecContext->height,frame->data,frame->linesize);   //图片信息转换
//        sws_freeContext(kSwsContext);
//        kSwsContext = 0;

//        frame->pts = next_pts++;
//        //frame->pts = i*(kAVStream->time_base.den)/((kAVStream->time_base.num)*24);

//        got_packer = 0;
//        ret = avcodec_encode_video2(kAVCodecContext,&kAVPacket,frame,&got_packer);  //8、编码、把一帧数据编码成AVPacket
//        if(ret < 0) {qDebug()<<"错误编码视频帧"<<ret; goto end;}

//        if(got_packer)
//        {
//            av_packet_rescale_ts(&kAVPacket, kAVCodecContext->time_base, kAVStream->time_base);
//            kAVPacket.stream_index = kAVStream->index;
//            ret = av_write_frame(kAVFormatContext, &kAVPacket); /*将压缩帧写入媒体文件。 */
//            av_free_packet(&kAVPacket);
//        }else
//        {ret = 0;}
//        free(intBuffer);intBuffer = 0;
//        if(ret<0){ qDebug()<<"写入video文件失败"<<ret<<kAVPacket.stream_index; break; }
//    }

//    /*  选择写预告片，如果有的话。预告片必须在你之前写好 当你写标题时关闭CodecContexts打开;否则
//        av_write_trailer()可以尝试使用被释放的内存  av_codec_close()。要编码的流 */
//    av_write_trailer(kAVFormatContext);

//end:
//    /* 关闭每个编解码器。 */
//    avcodec_free_context(&kAVCodecContext);
//    av_frame_free(&frame);

//    if (!(kAVOutputFormat->flags & AVFMT_NOFILE))
//        avio_closep(&kAVFormatContext->pb);/*关闭输出文件*/


//    avformat_free_context(kAVFormatContext);   /*释放上下文*/
}

bool isMOV(QString filename){
    filename = filename.toLower();
    int lastindex = filename.lastIndexOf(".");
    QString type = "";
    for (int i = lastindex+1;i<filename.length();i++){
        type += filename[i];
    }
    if (type == "mov"){
        return true;
    }
    return false;
}
