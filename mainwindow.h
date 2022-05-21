#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QVideoWidget>
#include<QMediaPlayer>
#include<QCloseEvent>
#include<QAudioOutput>
#include"qcustomplot.h"
#include"judge_type.h"

//#include"openfilethread.h"
#include"ReverseDecode.h"
#include"ReverseDecode_Audio.h"
#include"PreviewFrame.h"
#include"WAVFILEHEADER.h"
#include"resolve_wav_wave.h"
#include"wavefile.h"
#include"get_audio_wave.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    double availableScreenX;
    double availableScreenY;
    int type;
    QQueue<float> m_dataQueue;
    int m_bufferSize = 50;
    int dontshow = false;
    int dontpreview = false;
    int max;
    int min;
    float m_magnification;
    QCPGraphDataContainer* m_drawBuffer;
    qint64 ori_position = 0;
    qint64 old_position = 0;
    double old_wave_value = 0.;
    ReverseDecode DecodeWork;
    ReverseDecode_Audio DecodeWorkAudio;
    PreviewFrame previewFrame;
    Ui::MainWindow *ui;
    QMediaPlayer * mediaplayer;
    QMediaPlayer* mediaplayer2;
    WAVFILEHEADER WavFileHeader;
    QTimer*  m_pTimer;
    QTimer*  m_pTimer_preframe;
    QTimer*  m_pTimer_fullscreen;
    int zero_tolerence = 0;

    bool continue_;
    bool isFullScreen;
    bool isReverse;

    QString filepath; // 文件
    QStringList playList;//播放列表
    int current_index;
    int mouse_x;
    int mouse_y;
    qint64 reverse_duration;
    qint64 pause_time;
    qint64 last_begin_to_reverse;
    QString file_reverse;
    Audio_WAVE audio_wave;
    int height;

    int preframe_mouse_x;


//    static QAudioOutput        *audioOutput;
//    static QIODevice           *streamOut;

    void initPlayList();
    void deleteInPlayList(QString filename);
    int findInPlayList(QString filename);
    void addInPlayList(QString filename);
    void setFirseInPlayList(int index);


    void rewriteFile();

    void getNextAccessible(int first_index);
    void getPreviousAccessible(int first_index);

    void back();
    void forward();

    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *e);

    void parseWVV();

    void doBeforeChangeMedia(QString nextFilename);

    void playCacheFile();

    void recoverFromCacheFile();

    bool isCacheFile = false;

    int ori_widget_x;
    int ori_widget_y;
    int ori_widget_width;
    int ori_widget_height;

    int ori_widget_2_x;
    int ori_widget_2_y;
    int ori_widget_2_width;
    int ori_widget_2_height;

    int ori_widget_3_x;
    int ori_widget_3_y;
    int ori_widget_3_width;
    int ori_widget_3_height;


    int ori_horizontalSlider_x;
    int ori_horizontalSlider_y;
    int ori_horizontalSlider_width;
    int ori_horizontalSlider_height;

    int ori_horizontalSlider_2_x;
    int ori_horizontalSlider_2_y;
    int ori_horizontalSlider_2_width;
    int ori_horizontalSlider_2_height;




    int ori_toolbutton_10_x;
    int ori_toolbutton_10_y;
    int ori_toolbutton_10_width;
    int ori_toolbutton_10_height;

    int ori_toolbutton_x;
    int ori_toolbutton_y;
    int ori_toolbutton_width;
    int ori_toolbutton_height;

    int ori_toolbutton_2_x;
    int ori_toolbutton_2_y;
    int ori_toolbutton_2_width;
    int ori_toolbutton_2_height;

    int ori_toolbutton_3_x;
    int ori_toolbutton_3_y;
    int ori_toolbutton_3_width;
    int ori_toolbutton_3_height;

    int ori_toolbutton_4_x;
    int ori_toolbutton_4_y;
    int ori_toolbutton_4_width;
    int ori_toolbutton_4_height;


    int ori_toolbutton_5_x;
    int ori_toolbutton_5_y;
    int ori_toolbutton_5_width;
    int ori_toolbutton_5_height;

    int ori_toolbutton_6_x;
    int ori_toolbutton_6_y;
    int ori_toolbutton_6_width;
    int ori_toolbutton_6_height;

    int ori_combox_x;
    int ori_combox_y;
    int ori_combox_width;
    int ori_combox_height;


    int ori_toolbutton_7_x;
    int ori_toolbutton_7_y;
    int ori_toolbutton_7_width;
    int ori_toolbutton_7_height;

    int ori_toolbutton_8_x;
    int ori_toolbutton_8_y;
    int ori_toolbutton_8_width;
    int ori_toolbutton_8_height;

    int ori_toolbutton_9_x;
    int ori_toolbutton_9_y;
    int ori_toolbutton_9_width;
    int ori_toolbutton_9_height;

    int ori_label_x;
    int ori_label_y;
    int ori_label_width;
    int ori_label_height;

    int ori_label_2_x;
    int ori_label_2_y;
    int ori_label_2_width;
    int ori_label_2_height;

    int ori_label_3_x;
    int ori_label_3_y;
    int ori_label_3_width;
    int ori_label_3_height;

    int ori_label_4_x;
    int ori_label_4_y;
    int ori_label_4_width;
    int ori_label_4_height;


    int ori_label_5_x;
    int ori_label_5_y;
    int ori_label_5_width;
    int ori_label_5_height;

    int ori_label_6_x;
    int ori_label_6_y;
    int ori_label_6_width;
    int ori_label_6_height;

    int ori_label_7_x;
    int ori_label_7_y;
    int ori_label_7_width;
    int ori_label_7_height;

    int ori_verticalSlider_x;
    int ori_verticalSlider_y;
    int ori_verticalSlider_width;
    int ori_verticalSlider_height;

    QString ori_filename;








signals:
    void playListChanged();
    void unlock_signal();
    void callVideoStop();



private slots:
    //播放函数
    void play();
    //获取播放状态
    void mediaStateChanged_0(QMediaPlayer::MediaStatus status);
    void mediaStateChanged(QMediaPlayer::State state);
    //改变播放进度位置
    void postionChanged(qint64 position);
    //获取播放位置
    void setPosition(int postion);
    //获取播放长度
    void durationChanged(qint64 duration);

    void on_toolButton_clicked();
    void on_horizontalSlider_sliderMoved(int position);

    void handleError();
    void on_toolButton_2_clicked();

    void reloadListWidget();

    void closeEvent(QCloseEvent *event);


    void on_listWidget_doubleClicked(const QModelIndex &index);
    void on_toolButton_3_clicked();
    void on_toolButton_4_clicked();
    void on_listWidget_customContextMenuRequested(const QPoint &pos);

    void deleteItemSlot();
    void reverseItemSlot();

    void on_horizontalSlider_sliderPressed();
    void on_horizontalSlider_actionTriggered(int action);
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void updateInfo();

//    void ProcessFrame(QVideoFrame &frame);

//    void presentframe(const QVideoFrame & frame);

    void keyPressEvent(QKeyEvent *e);


    void on_toolButton_5_clicked();
    void on_toolButton_6_clicked();
    void on_toolButton_7_clicked();
    void on_toolButton_8_clicked();
    void on_verticalSlider_sliderMoved(int position);
    void on_listWidget_currentTextChanged(const QString &currentText);
    void on_toolButton_9_clicked();

    void threadFinished();

    void slotGetCurrentTime(qint64);
    void on_horizontalSlider_2_sliderMoved(int position);

    void on_horizontalSlider_2_valueChanged(int value);

    int openCodecContext(const AVFormatContext* pFormatCtx, int* pStreamIndex, enum AVMediaType type, AVCodecContext** ppCodecCtx);

    void setPreviewFrame(QImage);
//    void restartPreviewFrame();
    void ffmpegtest(double);
//    void saveFrame(AVFrame* pFrame, int width, int height, int iFrame);
    void testWav();
    void on_timer_timeout();
    void on_timer_timeout_fullscreen();


    void on_toolButton_10_clicked();

    void sleepforms();

    void threadFinished2();
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listWidget_currentRowChanged(int currentRow);
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_clicked(const QModelIndex &index);

    void no_video_handle();

    void videosleep(qint64);
    void audiosleep(qint64);

    void set_audio_s_video_time(qint64);

    void resizeEvent( QResizeEvent* e) override;

    void setCallBack();

    void start_timer();

    void stoptimer();
};

#endif // MAINWINDOW_H
