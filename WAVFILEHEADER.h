#ifndef WAVFILEHEADER_H
#define WAVFILEHEADER_H

// wav文件头信息结构
struct WAVFILEHEADER
{
//    // RIFF 头;
    char RiffName[4];
    unsigned long nRiffLength;

    // 数据类型标识符;
    char WavName[4];

    // 格式块中的块头;
    char FmtName[4];
    unsigned long nFmtLength;

    // 格式块中的块数据;
    unsigned short nAudioFormat;
    unsigned short nChannleNumber;
    unsigned long nSampleRate;
    unsigned long nBytesPerSecond;
    unsigned short nBytesPerSample;
    unsigned short nBitsPerSample;

    // 扩展信息(附加信息),根据 nFmtLength 来判断;
    // 扩展域大小;
    unsigned short nAppendMessage;
    // 扩展域信息数据;
    char* AppendMessageData;

    //Fact块,可选字段，一般当wav文件由某些软件转化而成，则包含该块和扩展信息;
    char FactName[4];
    unsigned long nFactLength;
    char FactData[4];

    // 数据块中的块头;
    char    DATANAME[4];
    unsigned long   nDataLength;

    // 以下是附加的一些计算信息;
    int fileDataSize;				// 文件音频数据大小;
    int fileHeaderSize;				// 文件头大小;
    int fileTotalSize;				// 文件总大小;


//    char ChunkID[4];    /* "RIFF" */

//     int ChunkSize;    /* 36 + Subchunk2Size */

//     char Format[4];    /* "WAVE" */


//     /* sub-chunk "fmt" */

//     char Subchunk1ID[4];    /* "fmt " */

//     int Subchunk1Size;    /* 16 for PCM */

//     short AudioFormat;    /* PCM = 1*/

//     short NumChannels;    /* Mono = 1, Stereo = 2, etc. */

//     int SampleRate;    /* 8000, 44100, etc. */

//     int ByteRate;    /* = SampleRate * NumChannels * BitsPerSample/8 */

//     short BlockAlign;    /* = NumChannels * BitsPerSample/8 */

//     short BitsPerSample;    /* 8bits, 16bits, etc. */

//     /* sub-chunk "data" */

//     char Subchunk2ID[4];    /* "data" */

//     int Subchunk2Size;    /* data size */

};



#endif // WAVFILEHEADER_H
