#include "get_audio_wave.h"

int Audio_WAVE::init(QString filename){
       format = nullptr;
       std::string str = filename.toStdString();
       url = str.c_str();
//       url = "D:/qtproject/Video_Player/video_test/123.wav";
       if (avformat_open_input(&format, url, nullptr, nullptr) < 0) {
           qDebug() << "open input failed";
           return -1;
       }
       avformat_find_stream_info(format, NULL);
//       av_opt_set(format->priv_data, "tune", "zerolatency", 0);
//       av_opt_set(format->priv_data, "preset", "superfast", 0);

       if (auto input_format = format->iformat) {
//           qDebug() << input_format->long_name;
       }

//       qDebug() << format->nb_streams;
       audio_codec = nullptr;
       codec = nullptr;

       for (auto i = 0; i < format->nb_streams; ++i) {
           codec = format->streams[i]->codec;
           if (codec->codec_type == AVMEDIA_TYPE_AUDIO) {
               audio_codec = avcodec_find_decoder(codec->codec_id);
               qDebug()<<"采样率"<<codec->sample_rate;
               audio_stream_index = i;
               break;
           }
       }

       if (audio_codec == nullptr) {
           qDebug()<< "no audio codec";
       }


       decoder = avcodec_alloc_context3(audio_codec);
//       decoder = codec;
       decoder->channels = codec->channels;
       decoder->sample_rate = codec->sample_rate;
       decoder->sample_fmt = codec->sample_fmt;
       decoder->codec_type = codec->codec_type;
       decoder->channel_layout = codec->channel_layout;
       if (avcodec_open2(decoder, audio_codec, nullptr) < 0) {
           qDebug() << "audio decoder open failed";
           return -1;
       }

//       qDebug() << "open decoder success: ";
       bytes_per_sample =  av_get_bytes_per_sample(decoder->sample_fmt);
       qDebug()<<"bytes_per_sample"<<bytes_per_sample;
       qDebug()<<"sample rate"<<decoder->sample_rate;
       qDebug()<<"channels"<<decoder->channels;
       packet = av_packet_alloc();
       frame = av_frame_alloc();
       return 1;

}
double Audio_WAVE::get_wave_value(int position){
//    AVPacket packet;
    double avg_A = 0;
    double ret_val = 0.5;
    std::vector<std::vector<uint8_t>> samples {};
//       av_opt_set(format->priv_data, "tune", "zerolatency", 0);
       av_seek_frame(format, -1, (double(position)/double(1000))*AV_TIME_BASE, AVSEEK_FLAG_ANY);
//       int r = av_read_frame(format, packet);
//       qDebug()<<packet->data;
       int flag = 0;
       while (av_read_frame(format, packet)>=0){
           if(packet->stream_index == audio_stream_index){
               flag = 1;
               break;
           }

       }
       if(flag == 0){
           return -1;
       }
       else{
           qDebug()<<"okok";
//           int ret;
//           avcodec_decode_audio4(codec, frame, &ret, packet);
           int r = avcodec_send_packet(decoder, packet);
           qDebug()<<"r"<<r;
           std::vector<uint8_t> bytes {};
////           int i= 0;
           int ret = avcodec_receive_frame(decoder, frame);

           qDebug()<<"ret"<<ret;
           if(ret >=0){
               uint64_t out_channel_layout;
               AVSampleFormat out_sample_fmt;
               int out_sample_rate;
               int out_channels;
               out_channel_layout = decoder->channel_layout;
               out_sample_fmt = AV_SAMPLE_FMT_S16;
               out_sample_rate = decoder->sample_rate;
               out_channels = av_get_channel_layout_nb_channels(out_channel_layout);
               SwrContext *swr_ctx = swr_alloc_set_opts(NULL, out_channel_layout, out_sample_fmt,out_sample_rate, decoder->channel_layout, decoder->sample_fmt, decoder->sample_rate, 0, 0);
               swr_init(swr_ctx);
               uint8_t * pcm = new uint8_t[frame->nb_samples * 2 * 2];
               uint8_t * data[2] = {0};
               data[0] = pcm;
               int len = swr_convert(swr_ctx,data,frame->nb_samples,(const uint8_t**)frame->data,frame->nb_samples);
               qDebug()<<"len"<<len;
               int sample = frame->nb_samples * 2 * 2;
               signed short *pcmData = new signed short[sample];
               memcpy(pcmData, pcm, sample);
               signed short ret = 0;
               if (sample > 0) {
                   int sum = 0;
                   signed short* pos = (signed short *)pcmData;
                   for (int i = 0; i < sample; i++)
                   {
                       sum += abs(*pos);
                       pos++;
                   }
//                   qDebug()<<"sum"<<sum;
//                   if(sum > max){
//                       max = sum;
//                   }
//                   if(sum < min){
//                       min = sum;
//                   }
//                   qDebug()<<"max"<<max;
//                   qDebug()<<"min"<<min;
                   ret_val = sum;
                   qDebug()<<"ret_val"<<ret_val;

//                   ret1 = sum;
//                   qDebug()<<"sum"<<sum;
//                   qDebug()<<position;
//                   if(position<800){

//                       ori = sum;
//                       qDebug()<<"指以下ori"<<sum;
//                   }
//                   else{
//                       qDebug()<<"ori"<<ori;
//                       qDebug()<<"倍数"<<sum/ori;
//                   }
               }
           }
       av_packet_unref(packet);
       return ret_val;
       }
//       }
//       else{
//           av_packet_unref(&packet);
//           return -1;
//       }

//=======================================================================
//               qDebug()<<"samples"<<frame->nb_samples;
//               for (auto sample = 0; sample < frame->nb_samples; ++sample) {
//                   for (auto channel = 0; channel < frame->channels; ++channel) {
//                       auto begin = frame->data[channel] + bytes_per_sample * sample;
//                       auto end = begin + bytes_per_sample;
//                       bytes.insert(bytes.end(), begin, end);
//                   }
//               }
//               auto sum = 0;
//               for(auto i = 0 ;i<bytes.size();i++){
//                   sum += qAbs(bytes[i]);
//               }
//               qDebug()<<"sum"<<sum;
//               avg_A = (double)sum / (double)bytes.size();
//           }

//           samples.push_back(std::move(bytes));

//           qDebug() << "frame size: " << samples.size();
//       }
//       return avg_A;
}


void Audio_WAVE::stop(){
    avcodec_close(decoder);
    avcodec_free_context(&decoder);
    avformat_close_input(&format);
}
