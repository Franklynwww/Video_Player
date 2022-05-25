#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"utils.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include<QFileDialog>
#include<QString>

#include <QFile>
#include<QMessageBox>
#include<QMediaMetaData>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>



enum Except{ EXCEP_ZERO,EXCEP_ONE};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

//    this->content_list.append(QMediaContent(QUrl::fromLocalFile("D:/qtproject/Video_Player/video_test/刘惜君、王赫野、天赐的声音 - 晚风心里吹 - 天赐的声音第三季 第6期.mkv")));

//    audio_wave.init("");




//    int a = judgetype("D:/qtproject/Video_Player/video_test/音乐磁场 - 尘缘8.mp4");
//    qDebug()<<(a==AUDIO_TYPE);
//    QTime t;
//    t.start();
//    while(t.elapsed()<500)
//        QCoreApplication::processEvents();
//    qDebug()<<"出来了";

//    ui->centralWidget->setWindowFlags(Qt::Window);
//    ui->centralWidget->showFullScreen();
//    qDebug()<<"available screenX"<<availableScreenX;
//    qDebug()<<"available screenY"<<availableScreenY;
    this->grabKeyboard();
    ui->setupUi(this);
    //设置主界面背景
    QPixmap pixmap(":/images/all.jpg");
    QPalette palette;
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);


//    mediaplayer->setMedia(QUrl::fromLocalFile("D:\\qtproject\\Video_Player\\video_test\\刘惜君、王赫野、天赐的声音 - 晚风心里吹.mkv"));
//    qDebug()<<"duratioo of cache"<<mediaplayer->duration();
//    mediaplayer->play();

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect deskRect = desktopWidget->availableGeometry();
    availableScreenX = deskRect.width();
    availableScreenY = deskRect.height();
//    ui->centralWidget->setWindowFlags (Qt::Window);

    setWindowFlags(windowFlags() &~ Qt::WindowMaximizeButtonHint);
    mediaplayer = new QMediaPlayer();
    //设置对应mediaplayer的QVideoWidget
    mediaplayer->setVideoOutput(ui->widget);

//    mediaplayer->setMedia(QUrl::fromLocalFile("D:/qtproject/Video_Player/video_test/fff.mkv"));
//    mediaplayer->play();


    ui->widget->move(availableScreenX/50,availableScreenY/50);
    ui->widget->resize((double)availableScreenX/2.3,(double)availableScreenY/2.3);

    ui->widget_2->move(availableScreenX/50,availableScreenY/50);
    ui->widget_2->resize((double)availableScreenX/2.3,(double)availableScreenY/2.3);

    ui->widget_3->move(availableScreenX/50,availableScreenY/50);
    ui->widget_3->resize((double)availableScreenX/2.3,(double)availableScreenY/2.3);


    ui->listWidget->move(ui->widget->x() + ui->widget->width() + availableScreenX/110, ui->widget->y());
    ui->listWidget->resize(availableScreenX/8,(double)availableScreenY/2.3);

    ui->textBrowser->move(ui->listWidget->x() + ui->listWidget->width() + availableScreenX/110, ui->widget->y());
    ui->textBrowser->resize(availableScreenX/8,(double)availableScreenY/2.3);

    ui->toolButton->move(ui->widget->x(),ui->widget->y() + ui->widget->height() + availableScreenY/50);
    ui->toolButton->resize(availableScreenX/32,availableScreenY/22);

    ui->toolButton_5->move(ui->toolButton->x() + ui->toolButton->width() + availableScreenX/120,ui->toolButton->y());
    ui->toolButton_5->resize(availableScreenX/32,availableScreenY/22);

    ui->toolButton_6->move(ui->toolButton_5->x() + ui->toolButton_5->width() + availableScreenX/120,ui->toolButton_5->y());
    ui->toolButton_6->resize(availableScreenX/32,availableScreenY/22);

    ui->horizontalSlider->move(ui->toolButton_6->x() + ui->toolButton_6->width() + availableScreenX/120,ui->toolButton_6->y());
    ui->horizontalSlider->resize(availableScreenX/4,availableScreenY/24);

    ui->toolButton_2->move(ui->horizontalSlider->x() + ui->horizontalSlider->width() + availableScreenX /110, ui->horizontalSlider->y());
    ui->toolButton_2->resize(availableScreenX/32,availableScreenY/22);

    ui->toolButton_3->move(ui->toolButton_2->x() + ui->toolButton_2->width() + availableScreenX/120,ui->toolButton_2->y());
    ui->toolButton_3->resize(availableScreenX/25,availableScreenY/22);

    ui->toolButton_4->move(ui->toolButton_3->x() + ui->toolButton_3->width() + availableScreenX/120,ui->toolButton_3->y());
    ui->toolButton_4->resize(availableScreenX/25,availableScreenY/22);

    ui->comboBox->move(ui->toolButton_4->x() + ui->toolButton_4->width() + availableScreenX/120,ui->toolButton_4->y());
    ui->comboBox->resize(availableScreenX/20,availableScreenY/22);

    ui->toolButton_7->move(ui->comboBox->x() + ui->comboBox->width() + availableScreenX/120,ui->comboBox->y());
    ui->toolButton_7->resize(availableScreenX/32,availableScreenY/22);

    ui->toolButton_8->move(ui->toolButton_7->x() + ui->toolButton_7->width() + availableScreenX/120,ui->toolButton_7->y());
    ui->toolButton_8->resize(availableScreenX/20,availableScreenY/22);


    ui->toolButton_10->move(ui->toolButton_8->x() + ui->toolButton_8->width() + availableScreenX/120,ui->toolButton_8->y());
    ui->toolButton_10->resize(availableScreenX/20,availableScreenY/22);

    ui->verticalSlider->move(ui->toolButton_10->x() + ui->toolButton_10->width() + availableScreenX/120,ui->toolButton_10->y() - availableScreenY/5 + ui->toolButton_10->height());
    ui->verticalSlider->resize(availableScreenX/50,availableScreenY/5);

    ui->label->move(ui->horizontalSlider->x() + ui->horizontalSlider->width() - availableScreenX/18, ui->horizontalSlider->y() - availableScreenY/98);
    ui->label->resize(availableScreenX/18,availableScreenY/50);

    ui->label_3->move(ui->label->x() - 10, ui->label->y());
    ui->label_3->resize(9,availableScreenY/50);
//    ui->label_3->setText("/");

    ui->label_2->move(ui->label_3->x() - availableScreenX/18 - 2, ui->label->y());
    ui->label_2->resize(availableScreenX/18,availableScreenY/50);


    ui->label_4->resize(availableScreenX/10,availableScreenY/8);


    ui->toolButton_9->move(ui->toolButton->x(),ui->toolButton->y());
    ui->toolButton_9->resize(availableScreenX/32,availableScreenY/22);

    ui->horizontalSlider_2->move(ui->toolButton_9->x() + ui->toolButton_9->width()+availableScreenX/120,ui->toolButton->y());
    ui->horizontalSlider_2->resize(availableScreenX/4 + availableScreenX/15, availableScreenY/22);

    ui->label_6->move(ui->horizontalSlider_2->x() + ui->horizontalSlider_2->width() - availableScreenX/18, ui->horizontalSlider_2->y() - availableScreenY/98);
    ui->label_6->resize(availableScreenX/18,availableScreenY/50);

    ui->label_7->move(ui->label_6->x() - 10, ui->label_6->y());
    ui->label_7->resize(9,availableScreenY/50);
//    ui->label_3->setText("/");

    ui->label_5->move(ui->label_7->x() - availableScreenX/18 - 2, ui->label_6->y());
    ui->label_5->resize(availableScreenX/18,availableScreenY/50);

//    ui->widget_2->resize(100,1000);
//    ui->widget_3->resize(100,1000);
//    ui->listWidget->resize(100,1000);
//    ui->textBrowser->resize(100,1000);

//    ui->centralWidget->setWindowFlag(Qt::Window);
    ui->centralWidget->setFixedSize((double)availableScreenX/1.15,(double)availableScreenY/1.7);


//    ui->centralWidget->move(availableScreenX*0.25,availableScreenY*0.25);
//    ui->centralWidget->resize(1300,2300);
//    ui->centralWidget->
//    ui->centralWidget->setWindowFlags (Qt::SubWindow);
//    qDebug()<<QDir::currentPath()+"/小蓓蕾组合 - 当我们同在一起.mkv";
//    this->mediaplayer->setMedia(QUrl::fromLocalFile(QDir::currentPath()+"/小蓓蕾组合 - 当我们同在一起.mkv"));
//    this->play();

    //设置播放按钮
    ui->toolButton->raise();
    ui->toolButton->setToolTip("播放");
    ui->toolButton->setAutoRaise(false);

    ui->toolButton->setIcon(QPixmap(":/images/play.png"));
    //设置打开文件按钮
    ui->toolButton_2->setToolTip("打开文件");
    ui->toolButton_2->setAutoRaise(true);
    ui->toolButton_2->setIcon(QPixmap(":/images/openfile.png"));
    //设置ListWidget
    //设置其他地方按钮
    ui->toolButton_3->setText("下一首");
    ui->toolButton_4->setText("上一首");
    ui->label->setText(": : :");
    ui->label_2->setText(": : :");
    ui->toolButton_5->setToolTip("快退");
    ui->toolButton_5->setIcon(QPixmap(":/images/back.png"));
    ui->toolButton_6->setToolTip("快进");
    ui->toolButton_6->setIcon(QPixmap(":/images/forward.png"));
    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);
    ui->label_7->setVisible(false);


//    ui->listWidget->setStyleSheet(
//    "QListWidget::item{background-color:rgba(255,255,255,1);border-width:2px;border-radius:4px;margin:4px 0px 0px 0px;}"
//    "QListWidget::item:hover{background-color:rgba(223,223,223,0.9);}"
//    "QListWidget::item::selected:active{background-color:rgba(220,220,220,1);color:black;}"
//    );

    //设置播放属性
    //1、监听信号变化函数,signal为内置的信号函数stateChanged，slot为自己定义的槽函数mediaStateChanged
//    connect(mediaplayer,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(mediaStateChanged_0(QMediaPlayer::MediaStatus)),Qt::DirectConnection); //播放状态变化
    connect(mediaplayer,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(mediaStateChanged(QMediaPlayer::State))); //播放状态变化
    //2、播放进度信号变化函数,signal为内置的信号函数positionChanged，slot为自己定义的槽函数postionChanged(qint64)
    connect(mediaplayer,SIGNAL(positionChanged(qint64)),this,SLOT(postionChanged(qint64))); //播放进度变化
    //3、媒体播放信号长度变化
    connect(mediaplayer,SIGNAL(durationChanged(qint64)),this,SLOT(durationChanged(qint64))); //信号长度
    //4、处理错误,signal为内置的信号函数error，slot为自己定义的槽函数handleError()
    connect(mediaplayer,SIGNAL(error(QMediaPlayer::Error)),this,SLOT(handleError()));
    //5.当内存中的playList发生变化且文件同时进行重写后，重新渲染ListWidget
    connect(this,SIGNAL(playListChanged(void)),this,SLOT(reloadListWidget()));

    //6. 获取文件信息
    connect(this->mediaplayer, SIGNAL(metaDataChanged()), this, SLOT(updateInfo()));
    // 7.获取鼠标移动事件
    this->setMouseTracking(true);
    this->centralWidget()->setMouseTracking(true);
    ui->widget->setMouseTracking(true);

    // 8. 获取鼠标点击事件
    ui->centralWidget->installEventFilter(this);
    ui->centralWidget->setMouseTracking(true);
//    ui->horizontalSlider->setAttribute(Qt::WA_Hover,true);//开启悬停事件
    ui->horizontalSlider->installEventFilter(this);
    ui->horizontalSlider->setMouseTracking(true);

    ui->horizontalSlider_2->installEventFilter(this);
    ui->horizontalSlider_2->setMouseTracking(true);
    ui->verticalSlider->installEventFilter(this);
    ui->verticalSlider->setMouseTracking(true);
    ui->toolButton->installEventFilter(this);
    ui->toolButton->setMouseTracking(true);

    ui->toolButton_2->installEventFilter(this);
    ui->toolButton_2->setMouseTracking(true);

    ui->toolButton_3->installEventFilter(this);
    ui->toolButton_3->setMouseTracking(true);

    ui->toolButton_4->installEventFilter(this);
    ui->toolButton_4->setMouseTracking(true);

    ui->toolButton_5->installEventFilter(this);
    ui->toolButton_5->setMouseTracking(true);

    ui->toolButton_6->installEventFilter(this);
    ui->toolButton_6->setMouseTracking(true);

    ui->toolButton_7->installEventFilter(this);
    ui->toolButton_7->setMouseTracking(true);

    ui->toolButton_8->installEventFilter(this);
    ui->toolButton_8->setMouseTracking(true);

    ui->toolButton_9->installEventFilter(this);
    ui->toolButton_9->setMouseTracking(true);

    ui->toolButton_10->installEventFilter(this);
    ui->toolButton_10->setMouseTracking(true);

    ui->comboBox->installEventFilter(this);
    ui->comboBox->setMouseTracking(true);

    ui->widget_3->installEventFilter(this);
    ui->widget_3->setMouseTracking(true);










    connect(ui->widget_2,SIGNAL(callvideosleep(qint64)),this,SLOT(videosleep(qint64)));

    connect(ui->widget_2,SIGNAL(callaudiosleep(qint64)),this,SLOT(audiosleep(qint64)));

    connect(ui->widget_2,SIGNAL(change_audio_s_video_time(qint64)),this,SLOT(set_audio_s_video_time(qint64)),Qt::DirectConnection);

//    ui->centralWidget->installEventFilter(this);
    // 9. 刷新列表
    connect(this,SIGNAL(playListChanged(void)),this,SLOT(reloadListWidget()));

    // 10.倒放
    //关联视频解码器
    connect(&DecodeWork, SIGNAL(SendOneFrame(QImage,double)), ui->widget_2, SLOT(slotSetOneFrame(QImage,double)),Qt::BlockingQueuedConnection);


    connect(this,SIGNAL(callVideoStop()),&DecodeWork,SLOT(finish()));

    //当前时间
    ui->horizontalSlider_2->installEventFilter(this);

    connect(ui->widget_2,SIGNAL(positionchanged(qint64)),this,SLOT(slotGetCurrentTime(qint64)),Qt::DirectConnection);
//    connect(&DecodeWork, SIGNAL(positionChanged1(qint64)), this, SLOT(slotGetCurrentTime(qint64)));

    connect(&DecodeWork,SIGNAL(isDone()),this,SLOT(threadFinished()));



    //10. 关联音频播放器
    connect(&DecodeWorkAudio,SIGNAL(SendOneAudioFrame(QByteArray,double)),ui->widget_2,SLOT(slotSetOneAudioFrame(QByteArray,double)),Qt::BlockingQueuedConnection);

//    connect(&DecodeWorkAudio, SIGNAL(positionChanged2(qint64)), this, SLOT(slotGetCurrentTime(qint64)));

    connect(&DecodeWorkAudio,SIGNAL(started2()),ui->widget_2,SLOT(threadStarted()));


    connect(&DecodeWorkAudio,SIGNAL(isDone2()),this,SLOT(threadFinished()));


    connect(&DecodeWork,SIGNAL(noVideo()),this,SLOT(no_video_handle()));


    connect(&DecodeWork2,SIGNAL(isDone()),this,SLOT(threadFinished2()));
    connect(&DecodeWorkAudio2,SIGNAL(isDone2()),this,SLOT(threadFinished2()));


    connect(&previewFrame,SIGNAL(isDone(QImage)),this,SLOT(setPreviewFrame(QImage)),Qt::BlockingQueuedConnection);

//    connect(&previewFrame,SIGNAL(notDone()),this,SLOT(restartPreviewFrame()));


    m_pTimer = new QTimer(this);
    m_pTimer->setSingleShot(true);
    m_pTimer_fullscreen = new QTimer(this);
    m_pTimer_preframe = new QTimer();
    m_pTimer_2 = new QTimer(this);


    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(on_timer_timeout()));
    connect(m_pTimer_fullscreen, SIGNAL(timeout()), this, SLOT(on_timer_timeout_fullscreen()));
    m_pTimer_preframe->moveToThread(&previewFrame);
    connect(&previewFrame,SIGNAL(begintoread()),this,SLOT(start_timer()),Qt::DirectConnection);
    connect(m_pTimer_preframe,SIGNAL(timeout()),this,SLOT(setCallBack()),Qt::DirectConnection);
    connect(&previewFrame,SIGNAL(finishedread()),this,SLOT(stoptimer()),Qt::DirectConnection);
    connect(m_pTimer_2, SIGNAL(timeout()),this,SLOT(on_time_timeout_2()));
//    connect(this,SIGNAL(unlock_signal()),ui->widget_2,SLOT(unlock_mutex()),Qt::DirectConnection);
    this->filepath = QDir::currentPath()+"/playList.txt";
    qDebug()<<this->filepath;
    //检查是否有文件
    QFile file(this->filepath);
    if(file.exists())
    {
        qDebug()<<"文件存在";
    }else{
       qDebug()<<"文件不存在,正在新建文件.";
       file.open( QIODevice::ReadWrite | QIODevice::Text );
       file.close();
    }

    //添加播放速度下拉选择
    QStringList plsySpdItems;
    plsySpdItems << "×0.5";
    plsySpdItems << "×0.8";
    plsySpdItems << "×1";
    plsySpdItems << "×1.2";
    plsySpdItems << "×1.5";
    plsySpdItems << "×2";
    plsySpdItems << "×3";
    plsySpdItems << "×4";
//    QComboBox* comboBoxPlaySpd = new QComboBox();
    ui->comboBox->setToolTip("倍速选择");
    ui->comboBox->addItems(plsySpdItems);//添加倍速选项
    ui->comboBox->setCurrentIndex(2);//设置默认速度1
//    ui->comboBox->setEditable(false);//设置为不可编辑

//    this->mediaplayer->setMedia(QUrl::fromLocalFile("D:/images/0.jpg"));
//    this->play();
    ui->toolButton_7->setToolTip("顺序播放");
    ui->toolButton_7->setIcon(QPixmap(":/images/series.jpg"));

    ui->verticalSlider->setValue(50);
    this->mediaplayer->setVolume(ui->verticalSlider->value());
    ui->widget_2->volumn = 0.5;

    ui->label_4->setVisible(false);
    ui->widget_2->setParent(ui->centralWidget);
    ui->widget_3->setVisible(false);
    ui->widget_3->setParent(ui->centralWidget);


    ui->widget_2->setVisible(false);
    ui->toolButton_9->setIcon(QPixmap(":/images/play.png"));
    ui->toolButton_9->setVisible(false);
    ui->horizontalSlider_2->setVisible(false);



    ui->toolButton_8->setText("倒放");

    initPlayList();


    ffmpegtest(113);

//    parseWVV();
//    testWav();
//    get_audio_wave();
//    height = ui->widget_4->height();

//    QPalette pal(ui->widget_4->palette());
//    pal.setColor(QPalette::Background, Qt::black);
//    ui->widget_4->setAutoFillBackground(true);
//    ui->widget_4->setPalette(pal);

    ui->toolButton_10->setText("全屏");

    this->ori_widget_x = ui->widget->x();
    this->ori_widget_y = ui->widget->x();
    this->ori_widget_width = ui->widget->width();
    this->ori_widget_height = ui->widget->height();
    this->ori_widget_2_x = ui->widget_2->x();
    this->ori_widget_2_y = ui->widget_2->y();
    this->ori_widget_2_width = ui->widget_2->width();
    this->ori_widget_2_height = ui->widget_2->height();
    this->ori_widget_3_x = ui->widget_3->x();
    this->ori_widget_3_y = ui->widget_3->y();
    this->ori_widget_3_width = ui->widget_3->width();
    this->ori_widget_3_height = ui->widget_3->height();
    this->ori_horizontalSlider_x = ui->horizontalSlider->x();
    this->ori_horizontalSlider_y = ui->horizontalSlider->y();
    this->ori_horizontalSlider_width = ui->horizontalSlider->width();
    this->ori_horizontalSlider_height = ui->horizontalSlider->height();

    this->ori_horizontalSlider_2_x = ui->horizontalSlider_2->x();
    this->ori_horizontalSlider_2_y = ui->horizontalSlider_2->y();
    this->ori_horizontalSlider_2_width = ui->horizontalSlider_2->width();
    this->ori_horizontalSlider_2_height = ui->horizontalSlider_2->height();

    this->ori_toolbutton_10_x = ui->toolButton_10->x();
    this->ori_toolbutton_10_y = ui->toolButton_10->y();
    this->ori_toolbutton_10_width = ui->toolButton_10->width();
    this->ori_toolbutton_10_height = ui->toolButton_10->height();

    this->ori_toolbutton_x = ui->toolButton->x();
    this->ori_toolbutton_y = ui->toolButton->y();
    this->ori_toolbutton_width = ui->toolButton->width();
    this->ori_toolbutton_height = ui->toolButton->height();

    this->ori_toolbutton_2_x = ui->toolButton_2->x();
    this->ori_toolbutton_2_y = ui->toolButton_2->y();
    this->ori_toolbutton_2_width = ui->toolButton_2->width();
    this->ori_toolbutton_2_height = ui->toolButton_2->height();

    this->ori_toolbutton_3_x = ui->toolButton_3->x();
    this->ori_toolbutton_3_y = ui->toolButton_3->y();
    this->ori_toolbutton_3_width = ui->toolButton_3->width();
    this->ori_toolbutton_3_height = ui->toolButton_3->height();

    this->ori_toolbutton_4_x = ui->toolButton_4->x();
    this->ori_toolbutton_4_y = ui->toolButton_4->y();
    this->ori_toolbutton_4_width = ui->toolButton_4->width();
    this->ori_toolbutton_4_height = ui->toolButton_4->height();

    this->ori_toolbutton_5_x = ui->toolButton_5->x();
    this->ori_toolbutton_5_y = ui->toolButton_5->y();
    this->ori_toolbutton_5_width = ui->toolButton_5->width();
    this->ori_toolbutton_5_height = ui->toolButton_5->height();

    this->ori_toolbutton_6_x = ui->toolButton_6->x();
    this->ori_toolbutton_6_y = ui->toolButton_6->y();
    this->ori_toolbutton_6_width = ui->toolButton_6->width();
    this->ori_toolbutton_6_height = ui->toolButton_6->height();

    this->ori_combox_x = ui->comboBox->x();
    this->ori_combox_y = ui->comboBox->y();
    this->ori_combox_width = ui->comboBox->width();
    this->ori_combox_height = ui->comboBox->height();

    this->ori_toolbutton_7_x = ui->toolButton_7->x();
    this->ori_toolbutton_7_y = ui->toolButton_7->y();
    this->ori_toolbutton_7_width = ui->toolButton_7->width();
    this->ori_toolbutton_7_height = ui->toolButton_7->height();

    this->ori_toolbutton_8_x = ui->toolButton_8->x();
    this->ori_toolbutton_8_y = ui->toolButton_8->y();
    this->ori_toolbutton_8_width = ui->toolButton_8->width();
    this->ori_toolbutton_8_height = ui->toolButton_8->height();

    this->ori_toolbutton_9_x = ui->toolButton_9->x();
    this->ori_toolbutton_9_y = ui->toolButton_9->y();
    this->ori_toolbutton_9_width = ui->toolButton_9->width();
    this->ori_toolbutton_9_height = ui->toolButton_9->height();

    this->ori_label_x = ui->label->x();
    this->ori_label_y = ui->label->y();
    this->ori_label_width = ui->label->width();
    this->ori_label_height = ui->label->height();

    this->ori_label_2_x = ui->label_2->x();
    this->ori_label_2_y = ui->label_2->y();
    this->ori_label_2_width = ui->label_2->width();
    this->ori_label_2_height = ui->label_2->height();

    this->ori_label_3_x = ui->label_3->x();
    this->ori_label_3_y = ui->label_3->y();
    this->ori_label_3_width = ui->label_3->width();
    this->ori_label_3_height = ui->label_3->height();

    this->ori_label_4_x = ui->label_4->x();
    this->ori_label_4_y = ui->label_4->y();
    this->ori_label_4_width = ui->label_4->width();
    this->ori_label_4_height = ui->label_4->height();

    this->ori_label_5_x = ui->label_5->x();
    this->ori_label_5_y = ui->label_5->y();
    this->ori_label_5_width = ui->label_5->width();
    this->ori_label_5_height = ui->label_5->height();

    this->ori_label_6_x = ui->label_6->x();
    this->ori_label_6_y = ui->label_6->y();
    this->ori_label_6_width = ui->label_6->width();
    this->ori_label_6_height = ui->label_6->height();

    this->ori_label_7_x = ui->label_7->x();
    this->ori_label_7_y = ui->label_7->y();
    this->ori_label_7_width = ui->label_7->width();
    this->ori_label_7_height = ui->label_7->height();

    this->ori_verticalSlider_x = ui->verticalSlider->x();
    this->ori_verticalSlider_y = ui->verticalSlider->y();
    this->ori_verticalSlider_width = ui->verticalSlider->width();
    this->ori_verticalSlider_height = ui->verticalSlider->height();







    this->isFullScreen = false;
    this->isReverse = false;

//    QPalette pal(ui->verticalSlider->palette());
//    pal.setColor(QPalette::Background, Qt::black);
//    ui->verticalSlider->setAutoFillBackground(true);
//    ui->verticalSlider->setPalette(pal);
//    ui->verticalSlider->raise();

    ui->widget->setAspectRatioMode(Qt::KeepAspectRatio);

    PreviewFrame::callback1 = false;

//    ui->widget_3->setBackground(QColor(255,255,255,0));


//    ui->widget_2->m_pTimer_audio = new QTimer(this);
//    ui->widget_2->m_pTimer_video = new QTimer(this);
//    connect(ui->widget_2->m_pTimer_audio, SIGNAL(timeout()), ui->widget_2, SLOT(on_timer_timeout_audio()));
//    connect(ui->widget_2->m_pTimer_video, SIGNAL(timeout()), ui->widget_2, SLOT(on_timer_timeout_video()));

//    connect(ui->widget_2,SIGNAL(main_sleep()),this,SLOT(sleepforms()),Qt::DirectConnection);


    QPalette label_palette;
    //label_palette.setColor(QPalette::Background, QColor(0, 0, 0));
    //label_palette.setColor(QPalette::Background,Qt::black);
    label_palette.setColor(QPalette::Background, QColor("white"));
    ui->label_5->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_5->setPalette(label_palette);
    ui->label_6->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_6->setPalette(label_palette);
    ui->label_7->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->label_7->setPalette(label_palette);
    ui->horizontalSlider_2->setAutoFillBackground(true); //这句很关键，否则背景色被默认windows替代
    ui->horizontalSlider_2->setPalette(label_palette);

//    ui->widget_4->setParent(ui->centralWidget);





}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mediaStateChanged_0(QMediaPlayer::MediaStatus status){
//    qDebug()<<"Jiaz";
//    if(status == QMediaPlayer::LoadedMedia){
//        qDebug()<<"Jia111111z";
//        this->play();
//    }
}
void MainWindow::play(){
//    while(this->mediaplayer->mediaStatus() != QMediaPlayer::LoadedMedia);
//    qDebug()<<"status"<<this->mediaplayer->mediaStatus();
//    qDebug()<<"state"<<this->mediaplayer->state();
    if(1){
    switch (this->mediaplayer->state()) {
    case QMediaPlayer::PlayingState: //Playing状态
        this->mediaplayer->pause();
        break;
    default:  // Pause或者Stop状态
        qDebug()<<this->mediaplayer->state();
//        VideoSurface * v = new VideoSurface();
//        this->mediaplayer->setVideoOutput(v);
//        this->mediaplayer->setMuted(true);
//        connect(v, SIGNAL(frameAvailable(QVideoFrame &)), this, SLOT(ProcessFrame(QVideoFrame &)));
        this->mediaplayer->play();
        break;
    }
    }
//    qDebug()<<3333;


}

void MainWindow::on_toolButton_clicked()
{
    play();
//    switch (this->mediaplayer->state()) {
//    case QMediaPlayer::PlayingState:
//        ui->toolButton->setToolTip("暂停");
//        ui->toolButton->setIcon(QPixmap(":/images/pause.png"));
//        break;
//    default:
//        ui->toolButton->setToolTip("播放");
//        ui->toolButton->setIcon(QPixmap(":/images/play.png"));
//        break;
//    }
}

void MainWindow::mediaStateChanged(QMediaPlayer::State state){//槽函数，触发条件：视频状态改变
    //
//    if((QMediaPlayer::MediaStatus)state == QMediaPlayer::LoadedMedia){
//        play();
//        return;
//    }
//    QMediaPlayer::MediaStatus status;
    switch (state) {
    case QMediaPlayer::PlayingState://Playing状态
        ui->toolButton->setToolTip("暂停");
        ui->toolButton->setIcon(QPixmap(":/images/pause.png"));
        break;
    default://Pause或者Stop状态
        ui->toolButton->setToolTip("播放");
        ui->toolButton->setIcon(QPixmap(":/images/play.png"));
        break;
    }
}

void MainWindow::postionChanged(qint64 position){//槽函数，触发条件：视频进度自动改变
    qDebug()<<"ori_pos"<<ori_pos;
//    qDebug()<<"status1"<<this->mediaplayer->mediaStatus();
    if(isCacheFile){
        qDebug()<<"cache_pos"<<position;
        qDebug()<<"cache_dur"<<mediaplayer->duration();
    }
    if(position == ori_pos && this->mediaplayer->state() == QMediaPlayer::PlayingState){
        zero_tolerence ++;
        qDebug()<<"zero"<<zero_tolerence;
        if(zero_tolerence == 10){
            notkey = true;
            QMessageBox::warning(this, tr("Error"),
                                           tr("解码时间超限制，正在尝试重新载入")
                                           );
            playCacheFile();
//            this->mediaplayer->setMedia(QUrl::fromLocalFile(""));
//            for(int i =0 ;i<100;i++){
//                qDebug()<<1;
//            }
//            mediaplayer->setMedia(QUrl::fromLocalFile(playList[current_index]));
//            mediaplayer->play();



//            playCacheFile();
//            this->mediaplayer->stop();
//            this->mediaplayer->set
//            this->mediaplayer->setMedia(QUrl::fromLocalFile(""));
//            this->mediaplayer->play();

//            for(int i=0;i<1000;i++){
//                int y = 1;
//            }

//            this->mediaplayer->stop();
//                        this->mediaplayer->setMedia(QUrl::fromLocalFile(""));
//                        for(int i = 0;i <100;i++){
//                            qDebug()<<1;
//                        }
//                        this->play();
////            doBeforeChangeMedia(this->playList[this->current_index]);
//            this->mediaplayer->setMedia(QUrl::fromLocalFile(this->playList[this->current_index]));
//            for(int i =0;i<100;i++){
//                qDebug()<<2;
//            }
//            this->play();
//            this->setPosition(0);
////            playCacheFile();
//////            this->mediaplayer->stop();
////            qDebug()<<"state"<<this->mediaplayer->state();
//////            qDebug()<<QDir::currentPath();
//////            this->mediaplayer->setMedia(QUrl::fromLocalFile(QDir::currentPath()+"/01.wmv"));
//////            delete mediaplayer;
//////            mediaplayer = new QMediaPlayer(this);
////            mediaplayer->setVideoOutput(ui->widget);
//////            this->mediaplayer->play();
////            this->mediaplayer->setMedia(QUrl::fromLocalFile(this->playList[this->current_index]));
//////            this->mediaplayer->setPosition(500);
////            this->mediaplayer->play();
            zero_tolerence = 0;
        }
    }
    if(position!=ori_pos){
        ori_pos = position;
        zero_tolerence = 0;
    }
    //
//    qDebug()<<this->mediaplayer->state();
//        QString curPath = this->playList[this->current_index];//获取当前应用程序目录
//        curPath += "\n";
//        if(this->mediaplayer->state() == QMediaPlayer::StoppedState){
//            curPath += "QMediaPlayer::StoppedState\n";
//        }
//        if(this->mediaplayer->state() == QMediaPlayer::PlayingState){
//            curPath += "QMediaPlayer::PlayingState\n";
//        }
//        if(this->mediaplayer->state() == QMediaPlayer::PausedState){
//            curPath += "QMediaPlayer::PausedState\n";
//        }



//        QFile f("D:\\status.txt");
//        if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
//        {
//            qDebug() << ("打开文件失败");
//        }
//        QTextStream txtOutput(&f);
//        QString str = curPath;
//        txtOutput << str << endl;
//        f.close();

//    qDebug()<<"out_pos"<<position;
//    qDebug()<<"out_old_pos"<<old_position;
//    qDebug()<<"current_index"<<this->current_index;
//    if(position < 1){

//    }
    ui->label_2->setText(transfer_to_std_time(position));
    ui->horizontalSlider->setValue(position);
    if(position !=0 && position >= this->mediaplayer->duration() && this->mediaplayer->duration()>0 && ui->toolButton_7->toolTip() == "顺序播放" && this->isCacheFile == false){
        getNextAccessible(this->current_index+1);
        return;
    }
    if(position !=0 && position >= this->mediaplayer->duration() && this->mediaplayer->duration()>0 && ui->toolButton_7->toolTip() == "单曲循环" && this->isCacheFile == false){

        ui->horizontalSlider->setMouseTracking(false);
        doBeforeChangeMedia(this->playList[this->current_index]);
        this->mediaplayer->setMedia(QUrl::fromLocalFile(this->playList[this->current_index]));

        this->play();
        ui->horizontalSlider->setMouseTracking(true);
        return;
    }
//    if(position!=0&& position >= this->mediaplayer->duration() && this->isCacheFile){
//        recoverFromCacheFile();
//        return;
//    }


//    if(position < ori_position + 300 * 50){
//        ui->widget_3->xAxis->setRange(ori_position,ori_position+300*50);
////            ui->widget_3->xAxis->setRange(position,300*100,Qt::AlignLeft);
//    }

//    else{
//        ui->widget_3->xAxis->setRange(position,300*50,Qt::AlignRight);
//        min = 0;
//        max = 5000;
////        if()
//        ui->widget_3->yAxis->setRange(min,max);
//    }

//    qDebug()<<"position"<<position;
//    qDebug()<<"ori_position"<<ori_position;
    if(this->type == AUDIO && this->dontshow == false){

    if(position - old_position >= 300){

//        qDebug()<<"进来了";
//        qDebug()<<"pos"<<position;
//        qDebug()<<"old_pos"<<old_position;
        double new_wave_value = audio_wave.get_wave_value(position);
        if(new_wave_value < 0){
            return;
        }
        if (m_dataQueue.size() >= m_bufferSize)
                m_dataQueue.dequeue();
            m_dataQueue.enqueue(new_wave_value);

//        if(new_wave_value > max ){
//            max = new_wave_value + 100;
//        }
//        if(new_wave_value < min){
//            min = new_wave_value - 100;
//        }

//        qDebug()<<"distance"<<new_wave_value-old_wave_value;

          old_position = position;
//        if(new_wave_value > 6000){
//            new_wave_value = 5900;
//        }

//        if(old_wave_value!=0){
//            int value = 0;
//            if((new_wave_value - old_wave_value)/old_wave_value > 2){
//                value = 2;
//            }
//            else{
//                if((new_wave_value - old_wave_value)/old_wave_value < -2){
//                    value = -2;
//                }
//            }
//            ui->widget_3->graph(0)->addData(position,(new_wave_value - old_wave_value)/old_wave_value);
//        }
//        else{
//            ui->widget_3->graph(0)->addData(position,0);
//        }


//        ui->widget_3->graph(0)->addData(position,new_wave_value);
//        ui->widget_3->yAxis->setRange(min,max);
          size_t size = m_dataQueue.size();
          qDebug()<<"size=="<<size;
          for (size_t j = size - 1; j; --j)
          {
              QCPGraphData* buff = (QCPGraphData*)m_drawBuffer->at(j);
              buff->value = m_dataQueue.at(j);
//              qDebug()<<"i:"<<j<<" value:"<<(QCPGraphData*)m_drawBuffer->at(j);
          }
          max = *std::max_element(m_dataQueue.begin(), m_dataQueue.end());
          min = *std::min_element(m_dataQueue.begin(), m_dataQueue.end());
          ui->widget_3->yAxis->setRange(min-100,max+100);
          ui->widget_3->replot(QCustomPlot::rpQueuedReplot);

//        ui->widget_3->replot();
//        old_wave_value = new_wave_value;
//       ui->widget_4->resize(ui->widget_4->width(),new_wave_value/1.5*height);

    }
    }


//    QVector<double> lineX(2),lineY(2);
//    lineX[0]=lineX[1]=(double)position*WavFileHeader.nSampleRate/1000;
//    qDebug()<<"lineX[0]"<<lineX[0];
//    lineY[0]=-100000;
//    lineY[1]=100000;
//    ui->widget_3->graph(1)->setData(lineX,lineY);

}

void MainWindow::setPosition(int position){
    //
    if(type == AUDIO){
    ui->widget_3->removeGraph(0);
    QSharedPointer<QCPGraphDataContainer> dataContainer = ui->widget_3->addGraph()->data();
    QVector<QCPGraphData> plotData(m_bufferSize);
    for (size_t j = 0; j < m_bufferSize; j++)
    {
        plotData[j].key = j;
        plotData[j].value = 0;
    }
    dataContainer->set(plotData, true);
    ui->widget_3->xAxis->setRange(0, m_bufferSize);
    m_dataQueue.clear();
    m_drawBuffer = ui->widget_3->graph()->data().data();
//    audio_wave.init();
    ori_position = position;
    old_position = ori_position;
//    old_wave_value = 0;
}
//    qDebug()<<"咋办呀";
    mediaplayer->setPosition(position);
//    qDebug()<<"set pos完了";
    
}

void MainWindow::durationChanged(qint64 duration){ //槽函数，触发条件：视频时长改变

    qDebug()<<"dur"<<duration;
    ui->label->setText(transfer_to_std_time(duration));
    ui->horizontalSlider->setRange(0,duration); 
//    this->play();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position) //槽函数，触发条件：主动移动进度条
{
    this->setPosition(position);
}

//播放异常的抛出
void MainWindow::handleError()
{
    //如果出现错误播放不了
//    ui->toolButton->setEnabled(false);

    qDebug() << "有错误发生了！";
}

void MainWindow::on_toolButton_2_clicked()
{

    QString filename;

    QT_TRY{
        filename = QFileDialog::getOpenFileName();
        if (filename == ""){
            return;
        }
        if(!isValidVideoFile(filename)){
            QMessageBox::warning(this, tr("Error"),
                                           tr("打开的文件不是音频格式或不受支持的音频格式")
                                           );
            return;
        }
        if(notkey || isReverse){
            QMessageBox::warning(this, tr("Error"),
                                           tr("此时不支持打开文件，请稍等再打开")
                                           );
            return;
        }
        this->mediaplayer->setMedia(QUrl::fromLocalFile(""));
        qDebug()<<"文件名"<<filename;
        for(int i =0 ;i<100;i++){
            qDebug()<<1;
        }
        ui->horizontalSlider->setMouseTracking(false);
        doBeforeChangeMedia(filename);
        mediaplayer->setMedia(QUrl::fromLocalFile(filename));
        this->play();




//        ui->toolButton->setAutoRaise(true);


        this->addInPlayList(filename);
//        this->mediaplayer->play();
        ui->horizontalSlider->setMouseTracking(true);
        ui->toolButton->setEnabled(true);



    }
    QT_CATCH(QMediaPlayer::Error e){
        qDebug()<<"出错了";
        return;
    }





}



void MainWindow::initPlayList(){
    //读取播放列表，加载到playList
    QFile file;
    QStringList fonts;
    QString line;
//    qDebug()<<path;
    file.setFileName(this->filepath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
//      QByteArray t ;
      while(!file.atEnd())
      {
          line = file.readLine();
          line.remove("\n");
          fonts<<line;
          qDebug()<<line;
      }
      file.close();

    }
    else{
        qDebug()<<"文件读取出错";
    }
    this->playList = fonts;
    this->current_index = -1;
    emit playListChanged();

//    ui->listWidget->addItems(fonts);//把各行添加到listwidget

}

int MainWindow::findInPlayList(QString filename){
    return playList.indexOf(filename);
}

void MainWindow::deleteInPlayList(QString filename){
    this->playList.removeOne(filename);
    emit playListChanged();
}

void MainWindow::addInPlayList(QString filename){
    if (filename == ""){
        return;
    }
    if (isValidVideoFile(filename) == false){
         QMessageBox::warning(this, tr("Error"),
                                        tr("打开的文件不是音频格式")
                                        );
        return;

    }

    if (this->findInPlayList(filename) != -1){
        this->current_index = this->findInPlayList(filename);
        emit playListChanged();
    }
    else{
        qDebug()<<"添加的文件名字"<<filename;
        this->playList.insert(0,filename);
        this->current_index = 0;
        emit playListChanged();
    }
}

//void MainWindow::addFile(QString filename){

//    QString cnt = filename;
//    QFile file(this->filepath);
//    file.open(QIODevice::Append|QIODevice::ReadWrite);
//    QTextStream out(&file);//写入
//    out << cnt << endl;
//    file.close();

//}

void MainWindow::rewriteFile(){
    QFile file(this->filepath);
    file.resize(0);
    file.open(QIODevice::ReadWrite);
    QTextStream out(&file);//写入
    qDebug()<<"写入前的list"<<playList;
    for (int i =0 ;i<this->playList.length();i++){
        QString cnt = this->playList[i] + "\n";
        out<<cnt;
    }
    file.close();
}

void MainWindow::reloadListWidget(){
    ui->listWidget->clear();
//    qDebug()<<"开始改变list";
    QStringList widget_list;
    for(int i=0;i<this->playList.length();i++){
        QString l = "";
        int lastIndex = ((QString)this->playList[i]).lastIndexOf("/");
        for (int j = lastIndex+1;j<this->playList[i].length();j++){
            l += this->playList[i][j];
        }
        l+="\n";
        l+="(";
        l+=playList[i];
        l+=")";
        widget_list.append(l);
    }
    ui->listWidget->addItems(widget_list);//把各行添加到listwidget

    for(int i = 0;i<this->playList.length();i++){
        if (i == this->current_index){
            ui->listWidget->item(i)->setTextColor(QColor(125,125,125));
        }
        else{
            ui->listWidget->item(i)->setTextColor(QColor(0,0,0));
        }
    }
//    qDebug()<<"结束改变list";

}

void MainWindow::closeEvent(QCloseEvent *event)

{

QMessageBox::StandardButton button;

    button=QMessageBox::question(this,tr("退出程序"),QString(tr("确认退出程序")),QMessageBox::Yes|QMessageBox::No);

    if(button==QMessageBox::No)

    {

        event->ignore(); // 忽略退出信号，程序继续进行

    }

    else if(button==QMessageBox::Yes)

    {

        event->accept(); // 接受退出信号，程序退出

        DecodeWork.StopPlay();
        DecodeWorkAudio.StopPlay();

        emit unlock_signal();
//        audio_mutex.unlock();
//        video_mutex.unlock();
    }




    qDebug()<<"最后的list"<<playList;

    //TODO: 在退出窗口之前，实现希望做的操作
    rewriteFile();

}


void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    ui->horizontalSlider->setMouseTracking(false);
    int cur_index = index.row();
    QString item_text = ui->listWidget->item(cur_index)->text();
//    qDebug()<<item_text;

    QString filename = "";
    int line_change = item_text.lastIndexOf("\n");

    for(int j = line_change+2;j<item_text.length()-1;j++){
        filename += item_text[j];
    }
    qDebug()<<filename;
    QFile file(filename);
    if(file.exists())
    {
        this->mediaplayer->setMedia(QUrl::fromLocalFile(""));
        for(int i =0 ;i<100;i++){
            qDebug()<<1;
        }
        qDebug()<<"文件存在";
        this->current_index = cur_index;
        doBeforeChangeMedia(filename);
        this->mediaplayer->setMedia(QUrl::fromLocalFile(filename));
        this->play();
        ui->horizontalSlider->setMouseTracking(true);
        for(int i = 0;i<this->playList.length();i++){
            if (i == this->current_index){
                ui->listWidget->item(i)->setTextColor(QColor(125,125,125));
            }
            else{
                ui->listWidget->item(i)->setTextColor(QColor(0,0,0));
            }
        }
    }else{
       qDebug()<<"文件不存在.";
       if(this->current_index == -1){
           QMessageBox::warning(this, tr("Error"),
                                          tr("打开的文件已不存在")
                                          );
           this->playList.removeOne(filename);
           emit playListChanged();
           return;
       }

       if(cur_index == this->current_index){
           QMessageBox::warning(this, tr("Error"),
                                          tr("打开的文件已不存在，将尝试打开下一个")
                                          );
           this->playList.removeOne(filename);
           getNextAccessible(this->current_index);
           return;
       }
       QMessageBox::warning(this, tr("Error"),
                                      tr("打开的文件已不存在")
                                      );
       QString ori_filename = this->playList[this->current_index];
       this->playList.removeOne(filename);
       this->current_index = this->playList.indexOf(ori_filename);
//       qDebug()<<this->playList[this->current_index];
       emit playListChanged();

    }

    ui->horizontalSlider->setMouseTracking(true);

}

void MainWindow::on_toolButton_3_clicked()
{
    if (this->current_index == -1){
        return;
    }

    getNextAccessible(this->current_index+1);
//    int len = this->playList.length();
//    QString nextfilename = this->playList[(this->current_index+1)%len];
//    QFile file(nextfilename);
//    if(file.exists())
//    {
//        qDebug()<<"文件存在";
//        this->current_index = (this->current_index+1)%len;
//        this->mediaplayer->setMedia(QUrl::fromLocalFile(nextfilename));
//        this->play();
//        for(int i = 0;i<this->playList.length();i++){
//            if (i == this->current_index){
//                ui->listWidget->item(i)->setTextColor(QColor(125,125,125));
//            }
//            else{
//                ui->listWidget->item(i)->setTextColor(QColor(0,0,0));
//            }
//        }
//    }else{
//       qDebug()<<"文件不存在.";
//       QMessageBox::warning(this, tr("Error"),
//                                      tr("下一首的文件已不存在")
//                                      );
//       this->playList.removeOne(nextfilename);
//       emit playListChanged();

//    }
}

void MainWindow::on_toolButton_4_clicked()
{
    if (this->current_index == -1){
        return;
    }
    getPreviousAccessible(this->current_index-1);
//    int len = this->playList.length();
//    QString prefilename = this->playList[(this->current_index-1+len)%len];
//    QFile file(prefilename);
//    if(file.exists())
//    {
//        qDebug()<<"文件存在";
//        this->current_index = (this->current_index-1+len)%len;
//        this->mediaplayer->setMedia(QUrl::fromLocalFile(prefilename));
//        this->play();
//        for(int i = 0;i<this->playList.length();i++){
//            if (i == this->current_index){
//                ui->listWidget->item(i)->setTextColor(QColor(125,125,125));
//            }
//            else{
//                ui->listWidget->item(i)->setTextColor(QColor(0,0,0));
//            }
//        }
//    }else{
//       qDebug()<<"文件不存在.";
//       QMessageBox::warning(this, tr("Error"),
//                                      tr("下一首的文件已不存在")
//                                      );
//       this->playList.removeOne(prefilename);
//       qDebug()<<"删除后的playList"<<playList;
//       emit playListChanged();

//    }

}

void MainWindow::on_listWidget_customContextMenuRequested(const QPoint &pos)
{

    QListWidgetItem* curItem = ui->listWidget->itemAt(pos);
    if( curItem == NULL )
        return;

    QMenu *popMenu = new QMenu( this );
    QAction *deleteItem = new QAction(tr("Delete"), this);
//    QAction *reverseItem = new QAction(tr("Reverse"), this);
    popMenu->addAction( deleteItem );
//    popMenu->addAction( reverseItem );
    connect( deleteItem, SIGNAL(triggered() ), this, SLOT( deleteItemSlot()) );
//    connect( reverseItem, SIGNAL(triggered() ), this, SLOT(reverseItemSlot()) );
    popMenu->exec( QCursor::pos() );
//    delete popMenu;
//    delete deleteSeed;
//    delete clearSeeds;
}


void MainWindow::deleteItemSlot(){
    int ch = QMessageBox::warning(NULL, "Warning",
                                  "您确定要删除吗 ?",
                                  QMessageBox::Yes | QMessageBox::No,
                                  QMessageBox::No);

    if ( ch != QMessageBox::Yes )
        return;

    QListWidgetItem * item = ui->listWidget->currentItem();
    if( item == NULL )
        return;

    int curIndex = ui->listWidget->row(item);
    if(this->current_index == -1){
        this->playList.removeAt(curIndex);
        emit playListChanged();
        return;
    }

    QString ori_filename = this->playList[this->current_index];
    this->playList.removeAt(curIndex);

    qDebug()<<"curIndex"<<curIndex;
    qDebug()<<"this->current_index"<<this->current_index;
//    if (this->playList.length() == 0){
//        this->mediaplayer->setMedia(NULL);
//        this->current_index = -1;
//        this->play();
//        return;
//    }
    if (this->current_index != curIndex){
        this->current_index = this->playList.indexOf(ori_filename);
        emit playListChanged();
    }
    else{
        if (this->mediaplayer->state() == QMediaPlayer::PlayingState){
            getNextAccessible(curIndex);
        }
        else{
            this->mediaplayer->setMedia(NULL);
            this->current_index = -1;
//            this->play();
            emit playListChanged();
            return;
        }
    }




//    if (this->current_index == curIndex){
//        while (this->playList.length()>=1){
//            int len = this->playList.length();
//            qDebug()<<"删除前的playList"<<this->playList;
//            qDebug()<<"删除的id"<<this->current_index;
//            QString nextfilename = this->playList[this->current_index];
//            qDebug()<<"下一首"<<nextfilename;
//            QFile file(nextfilename);
//            if(file.exists())
//            {
//                qDebug()<<"文件存在";
//                this->current_index = this->current_index;
//                this->mediaplayer->setMedia(QUrl::fromLocalFile(nextfilename));
//                this->play();
//                for(int i = 0;i<this->playList.length();i++){
//                    if (i == this->current_index){
//                        ui->listWidget->item(i)->setTextColor(QColor(125,125,125));
//                    }
//                    else{
//                        ui->listWidget->item(i)->setTextColor(QColor(0,0,0));
//                    }
//                }
//                break;
//            }else{
//               qDebug()<<"文件不存在.";
//               QMessageBox::warning(this, tr("Error"),
//                                              tr("下一首的文件已不存在")
//                                              );
//               this->playList.removeOne(nextfilename);
//               emit playListChanged();

//            }
//        }
//        if (this->playList.length()==0){
//            this->mediaplayer->setMedia(NULL);
//            this->current_index = -1;
//            this->play();
//        }
//    }
//    else
//        ;



}



void MainWindow::reverseItemSlot(){

//    QListWidgetItem * item = ui->listWidget->currentItem();
//    if( item == NULL )
//        return;

//    QPainter painter(this);


//    this->mediaplayer->setMedia(NULL);
//    this->mediaplayer->play();
//    this->current_index = -1;
//    emit playListChanged();

//    QRect q(ui->widget->x(),ui->widget->y(),ui->widget->x()+ui->widget->width(),ui->widget->y()+ui->widget->height());
////    QString fileName="D:\\images\\0.jpg";

//    QPixmap map(fileName);
//    painter.drawPixmap(q,this->pixmaps[t]);

//    int curIndex = ui->listWidget->row(item);
//    if(this->current_index == -1){
//        this->playList.removeAt(curIndex);
//        emit playListChanged();
//        return;
//    }

//    QString ori_filename = this->playList[this->current_index];
//    this->playList.removeAt(curIndex);

//    qDebug()<<"curIndex"<<curIndex;
//    qDebug()<<"this->current_index"<<this->current_index;
////    if (this->playList.length() == 0){
////        this->mediaplayer->setMedia(NULL);
////        this->current_index = -1;
////        this->play();
////        return;
////    }
//    if (this->current_index != curIndex){
//        this->current_index = this->playList.indexOf(ori_filename);
//        emit playListChanged();
//    }
//    else{
//        if (this->mediaplayer->state() == QMediaPlayer::PlayingState){
//            getNextAccessible(curIndex);
//        }
//        else{
//            this->mediaplayer->setMedia(NULL);
//            this->current_index = -1;
//            this->play();
//            emit playListChanged();
//            return;
//        }
//    }




////    if (this->current_index == curIndex){
////        while (this->playList.length()>=1){
////            int len = this->playList.length();
////            qDebug()<<"删除前的playList"<<this->playList;
////            qDebug()<<"删除的id"<<this->current_index;
////            QString nextfilename = this->playList[this->current_index];
////            qDebug()<<"下一首"<<nextfilename;
////            QFile file(nextfilename);
////            if(file.exists())
////            {
////                qDebug()<<"文件存在";
////                this->current_index = this->current_index;
////                this->mediaplayer->setMedia(QUrl::fromLocalFile(nextfilename));
////                this->play();
////                for(int i = 0;i<this->playList.length();i++){
////                    if (i == this->current_index){
////                        ui->listWidget->item(i)->setTextColor(QColor(125,125,125));
////                    }
////                    else{
////                        ui->listWidget->item(i)->setTextColor(QColor(0,0,0));
////                    }
////                }
////                break;
////            }else{
////               qDebug()<<"文件不存在.";
////               QMessageBox::warning(this, tr("Error"),
////                                              tr("下一首的文件已不存在")
////                                              );
////               this->playList.removeOne(nextfilename);
////               emit playListChanged();

////            }
////        }
////        if (this->playList.length()==0){
////            this->mediaplayer->setMedia(NULL);
////            this->current_index = -1;
////            this->play();
////        }
////    }
////    else
////        ;



}



void MainWindow::getNextAccessible(int first_index){
    ui->horizontalSlider->setMouseTracking(false);
//    this->mediaplayer->stop();

//    this->mediaplayer->play();
    qDebug()<<"first_index"<<first_index;
    int cur_index = first_index;
    while (cur_index<this->playList.length()){
        QString nextfilename = this->playList[cur_index];
        QFile file(nextfilename);
        if (file.exists()){
            this->mediaplayer->setMedia(QUrl::fromLocalFile(""));
            for(int i =0 ;i<100;i++){
                qDebug()<<1;
            }
            this->current_index = cur_index;


//            this->mediaplayer->stop();
//            for(int i = 0;i <500;i++){
//                int y = 1;
//                qDebug()<<y;
//            }

//            this->mediaplayer->stop();
//            qDebug()<<"setmedia开始";
            doBeforeChangeMedia(nextfilename);
            this->mediaplayer->setMedia(QUrl::fromLocalFile(nextfilename));
            qDebug()<<"nextfile"<<nextfilename;
            qDebug()<<"setmedia结束";


//            while(!(QMediaPlayer::MediaStatus)this->mediaplayer->state() == QMediaPlayer::LoadedMedia);
//            this->mediaplayer->play();
            qDebug()<<"为何没有";
//            this->setPosition(0);
            this->play();
//            this->setPosition(0);
            ui->horizontalSlider->setMouseTracking(true);
            qDebug()<<"还好在呢";
//            for(int i = 0;i<this->playList.length();i++){
//                if (i == this->current_index){
//                    ui->listWidget->item(i)->setTextColor(QColor(125,125,125));
//                }
//                else{
//                    ui->listWidget->item(i)->setTextColor(QColor(0,0,0));
//                }
//            }
            qDebug()<<"染色了";
            emit playListChanged();
            return;
        }
        else{
            this->playList.removeAt(cur_index);
        }

    }
    cur_index = 0;
    while (this->playList.length()>0){
        QString nextfilename = this->playList[cur_index];
        QFile file(nextfilename);
        if (file.exists()){
            this->mediaplayer->setMedia(QUrl::fromLocalFile(""));
            for(int i =0 ;i<100;i++){
                qDebug()<<1;
            }
            this->current_index = cur_index;
            doBeforeChangeMedia(nextfilename);
            this->mediaplayer->setMedia(QUrl::fromLocalFile(nextfilename));
//            this->setPosition(0);
            this->play();
            ui->horizontalSlider->setMouseTracking(true);
            for(int i = 0;i<this->playList.length();i++){
                if (i == this->current_index){
                    ui->listWidget->item(i)->setTextColor(QColor(125,125,125));
                }
                else{
                    ui->listWidget->item(i)->setTextColor(QColor(0,0,0));
                }
            }
            emit playListChanged();
            return;
        }
        else{
            this->playList.removeAt(cur_index);
        }
    }
    if (this->playList.length() == 0){
        this->mediaplayer->setMedia(NULL);
        this->current_index = -1;
        this->play();
        ui->horizontalSlider->setMouseTracking(true);
        if(ui->widget->isVisible()){
            ui->widget->setVisible(false);
        }
        if(ui->widget_3->isVisible()){
            ui->widget_3->setVisible(false);
        }
        emit playListChanged();
        return;
    }


    ui->horizontalSlider->setMouseTracking(true);


}

void MainWindow::getPreviousAccessible(int first_index){
    ui->horizontalSlider->setMouseTracking(false);
//    this->mediaplayer->stop();

//    this->play();
    int cur_index = first_index;
    while (cur_index>=0 && this->playList.length()>0){
        QString prefilename = this->playList[cur_index];
        QFile file(prefilename);
        if (file.exists()){
            this->mediaplayer->setMedia(QUrl::fromLocalFile(""));
            for(int i =0 ;i<100;i++){
                qDebug()<<1;
            }
            this->current_index = cur_index;
            doBeforeChangeMedia(prefilename);
            this->mediaplayer->setMedia(QUrl::fromLocalFile(prefilename));
            this->play();
            ui->horizontalSlider->setMouseTracking(true);
//            for(int i = 0;i<this->playList.length();i++){
//                if (i == this->current_index){
//                    ui->listWidget->item(i)->setTextColor(QColor(125,125,125));
//                }
//                else{
//                    ui->listWidget->item(i)->setTextColor(QColor(0,0,0));
//                }
//            }
//            qDebug()<<"上一首染色了；";
            emit playListChanged();
            return;
        }
        else{
            this->playList.removeAt(cur_index);
            cur_index --;
        }

    }
    cur_index = this->playList.length() - 1;
    while (this->playList.length()>0){
        QString prefilename = this->playList[cur_index];
        QFile file(prefilename);
        if (file.exists()){
            this->mediaplayer->setMedia(QUrl::fromLocalFile(""));
            for(int i =0 ;i<100;i++){
                qDebug()<<1;
            }
            this->current_index = cur_index;
            doBeforeChangeMedia(prefilename);
            this->mediaplayer->setMedia(QUrl::fromLocalFile(prefilename));

            this->play();
            ui->horizontalSlider->setMouseTracking(true);
            for(int i = 0;i<this->playList.length();i++){
                if (i == this->current_index){
                    ui->listWidget->item(i)->setTextColor(QColor(125,125,125));
                }
                else{
                    ui->listWidget->item(i)->setTextColor(QColor(0,0,0));
                }
            }
            emit playListChanged();
            return;
        }
        else{
            this->playList.removeAt(cur_index);
            cur_index --;
        }

    }

    if (this->playList.length() == 0){
        this->mediaplayer->setMedia(NULL);
        this->current_index = -1;
        this->play();
        ui->horizontalSlider->setMouseTracking(true);
        emit playListChanged();
        return;
    }

    ui->horizontalSlider->setMouseTracking(true);

}



void MainWindow::on_horizontalSlider_sliderPressed()
{

}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{

//    QSize q = ui->horizontalSlider->size();
//    qDebug()<<this->mouse_x;
//    qDebug()<<q.width();

}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    this->mouse_x = event->x();
    this->mouse_y = event->y();

}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{

    int const current_index = ui->comboBox->currentIndex();
//    ui->comboBox->setCurrentIndex(current_index);//设置默认速度1
//    qDebug()<<current_index;
    QString current_text = arg1;
    qDebug()<<current_text;
    QString speed_val = "";
    for (int var = 1; var < current_text.length(); ++var) {
        speed_val+=current_text[var];
    }
    this->mediaplayer->setPlaybackRate(qreal(speed_val.toFloat()));



}

void MainWindow::updateInfo(){
    ui->textBrowser->clear();
    qDebug()<<this->mediaplayer->isMetaDataAvailable();
//        qDebug()<<this->mediaplayer->metaData(QMediaMetaData::AlbumTitle).toString();
    foreach(QString str,this->mediaplayer->availableMetaData()){
        QString info = str + ":";
        qDebug()<<str<<"   :"<<this->mediaplayer->metaData(str).toString().toUtf8().data();
        QString  data = this->mediaplayer->metaData(str).toString().toUtf8().data();
        info += data;
        if (str == "Duration"){
            info += "ms";
            info += "("+transfer_to_std_time(data.toInt())+")";
        }
        ui->textBrowser->append(info);
    }
//    ui->textBrowser->setText(info);
}


//void MainWindow::ProcessFrame(QVideoFrame &frame)
//{   if (frame.endTime() == this->pause_time){
//    static int count = 0;
//    qDebug() << "=============ProcessFrame===============";
//    qDebug() << "width : " << frame.width() << " height : " << frame.height();
//    qDebug() << "start time : " << frame.startTime()/1000 << "ms";
//    qDebug() << "end time : " << frame.endTime()/1000 << "ms";
//    qDebug() << "pixelFormat :" << frame.pixelFormat();

//    frame.map(QAbstractVideoBuffer::ReadOnly);
//    QImage recvImage(frame.bits(), frame.width(), frame.height(), QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));
//    recvImage.save(QString("D:/images/%1.jpg").arg(count), "JPG");
//    qDebug() << "frame data size :" << frame.mappedBytes();
////    update();
//    frame.unmap();
//    }
//}

//实现mouseMoveEvent
void MainWindow::mouseMoveEvent(QMouseEvent *event){
//    qDebug()<<"ok";
//    int mouse_x = event->x();
//    int mouse_y = event->y();
//    qDebug()<<"mouse_x"<<mouse_x;
//    qDebug()<<"mouse_y"<<mouse_y;
//    qDebug()<<"slider_x"<<ui->horizontalSlider->x();
//    qDebug()<<"slider_x"<<ui->horizontalSlider->y();
//    qDebug()<<"slider_width"<<ui->horizontalSlider->width();
//    qDebug()<<"slider_height"<<ui->horizontalSlider->height();



////    if (ui->horizontalSlider->geometry().contains(this->mapFromGlobal(QCursor::pos())))
//    if(mouse_x>=ui->horizontalSlider->x() && mouse_x<= ui->horizontalSlider->x()+ui->horizontalSlider->width()
//            && mouse_y>=ui->horizontalSlider->y()&& mouse_y<=ui->horizontalSlider->y()+ui->horizontalSlider->height())
//    {

////        this->mediaplayer->stop();
////        previewFrame.stop();
////         do something...
//        qDebug()<<"mouse_x"<<mouse_x;
//        qDebug()<<"mouse_y"<<mouse_y;
//        qDebug()<<"slider_x"<<ui->horizontalSlider->x();
//        qDebug()<<"slider_y"<<ui->horizontalSlider->y();
//        qDebug()<<111;
//        if (this->current_index != -1){
//        qint64 position = (mouse_x-ui->horizontalSlider->x())*ui->horizontalSlider->maximum()/ui->horizontalSlider->width();
//        this->pause_time = position;
//        ui->label_4->move(mouse_x,ui->label_4->y());
//        ui->label_4->setPixmap(QPixmap("D:\\images\\72.jpg"));
//        previewFrame.time = position / 1000;
////        previewFrame.time = 60;
//        previewFrame.filename = this->playList[this->current_index];
//        previewFrame.start();
//        ui->label_4->setScaledContents(true);
//        ui->label_4->setVisible(true);
////        VideoSurface * videoSurface = new VideoSurface();
////        qDebug()<<"max_len"<<transfer_to_std_time(ui->horizontalSlider->maximum());
////        qDebug()<<"position"<<transfer_to_std_time(position);
////        this->mediaplayer2->setVideoOutput(videoSurface);
////        this->mediaplayer2->setMedia(QUrl(this->playList[this->current_index]));
////        connect(videoSurface, SIGNAL(frameAvailable(QVideoFrame &)), this, SLOT(ProcessFrame(QVideoFrame &)));
////        this->mediaplayer2->setPlaybackRate(qreal(10));
////        this->mediaplayer2->play();


////        OpenFileThread * thread = new OpenFileThread();
////        thread->position = position;
////        thread->filename = this->playList[this->current_index];
////        thread->start();
//    }
//    }
//    else{
////        previewFrame.stop();
//        ui->label_4->setVisible(false);
//        previewFrame.stop();
//    }
////    emit mouseMoved(event);
}




//使用eventFilter实现mousePressEvent
bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{

    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e);
    int mouse_x = mouseEvent->x();
    int mouse_y = mouseEvent->y();
    continue_  = true;
//    qDebug()<<e->type();
//    qDebug()<<obj;
    if(this->isFullScreen == true && e->type() == QEvent::MouseMove){
        m_pTimer_fullscreen->stop();
        m_pTimer_fullscreen->start(5000);
//        qDebug()<<"设置了";
//        if((mouse_x>=ui->verticalSlider->x() && mouse_x<= ui->verticalSlider->x()+ui->verticalSlider->width()&& mouse_y>=ui->verticalSlider->y()&& mouse_y<=ui->verticalSlider->y()+ui->verticalSlider->height())){
//            qDebug()<<"在音量";
//            qDebug()<<"设置了";
//        }
//        if((mouse_x>=ui->horizontalSlider->x() && mouse_x<= ui->horizontalSlider->x()+ui->horizontalSlider->width()&& mouse_y>=ui->horizontalSlider->y()&& mouse_y<=ui->horizontalSlider->y()+ui->horizontalSlider->height())){
//            qDebug()<<"在水平上";
//            qDebug()<<"设置了";
//        }

        ui->centralWidget->setCursor(Qt::ArrowCursor); //显示鼠标
        if(!this->isReverse){
            ui->toolButton->setVisible(true);
            ui->horizontalSlider->setVisible(true);
            ui->label->setVisible(true);
            ui->label_2->setVisible(true);
            ui->label_3->setVisible(true);
//            ui->label_4->setVisible(true);
            ui->toolButton_5->setVisible(true);
            ui->toolButton_6->setVisible(true);

        }
        if(this->isReverse){
            ui->toolButton_9->setVisible(true);
            ui->horizontalSlider_2->setVisible(true);
            ui->label_5->setVisible(true);
            ui->label_6->setVisible(true);
            ui->label_7->setVisible(true);
        }
        ui->toolButton_2->setVisible(true);
        ui->toolButton_3->setVisible(true);
        ui->toolButton_4->setVisible(true);
        ui->toolButton_7->setVisible(true);
        ui->toolButton_8->setVisible(true);
        ui->toolButton_10->setVisible(true);
        ui->comboBox->setVisible(true);
        ui->verticalSlider->setVisible(true);


    }
//    if(this->isFullScreen == false){
////        qDebug()<<"设置了";

//        ui->centralWidget->setCursor(Qt::ArrowCursor); //显示鼠标

//    }
    if(e->type() == QEvent::MouseMove && !(mouse_x>=ui->horizontalSlider->x() && mouse_x<= ui->horizontalSlider->x()+ui->horizontalSlider->width()&& mouse_y>=ui->horizontalSlider->y()&& mouse_y<=ui->horizontalSlider->y()+ui->horizontalSlider->height())){
        ui->label_4->setVisible(false);
        previewFrame.m_run = 2;
        m_pTimer->stop();

//        return true;
//        previewFrame.stop();


//        qDebug()<<"出去了";


    }

//    if((mouse_x>=ui->horizontalSlider->x() && mouse_x<= ui->horizontalSlider->x()+ui->horizontalSlider->width()&& mouse_y>=ui->horizontalSlider->y()&& mouse_y<=ui->horizontalSlider->y()+ui->horizontalSlider->height())){
//        //            qDebug()<<"m_x"<<mouse_x;
//        //            qDebug()<<"m_y"<<mouse_y;
//        //            qDebug()<<"slider_x"<<ui->horizontalSlider->x();
//        //            qDebug()<<"slider_y"<<ui->horizontalSlider->y();
//        //            previewFrame.stop();

//        //            qDebug()<<111;
//                    if (this->current_index != -1){
//                    previewFrame.stop();
////                    previewFrame.m_run = 1;
//                    qint64 position = mouse_x*ui->horizontalSlider->maximum()/ui->horizontalSlider->width();
//                    qDebug()<<"pos"<<transfer_to_std_time(position);
//                    this->pause_time = position;
//                    ui->label_4->move(mouse_x+ui->horizontalSlider->x(),ui->horizontalSlider->y()-ui->label_4->height());
//                    ui->label_4->setPixmap(QPixmap("D:\\images\\72.jpg"));
//                    previewFrame.time = position / 1000;
//            //        previewFrame.time = 60;
//                    previewFrame.filename = this->playList[this->current_index];
//                    previewFrame.start();
//                    ui->label_4->setScaledContents(true);
//                    ui->label_4->setVisible(true);

//                    }


//    }


//    int mouse_y = ui->centralWidget->height() - mouseEvent->y() - 20;
    if (obj == ui->horizontalSlider)
    {
//        qDebug()<<e->type();
//        qDebug()<<obj;
//        qDebug()<<"进来了";



        if(e->type() == QEvent::MouseMove){
//            qDebug()<<"悬停了";
//            qDebug()<<"m_x"<<mouse_x;
//            qDebug()<<"m_y"<<mouse_y;
//            qDebug()<<"slider_x"<<ui->horizontalSlider->x();
//            qDebug()<<"slider_y"<<ui->horizontalSlider->y();
//            previewFrame.stop();

//            qDebug()<<111;
//            if (this->current_index != -1){

////                else{
//            continue_ = false;
//            if(previewFrame.m_run == 0){
//                continue_ = true;
//            }
//            previewFrame.stop();

//            previewFrame.start();
//            this->mouse_x = mouse_x;
//            this->mouse_y = mouse_y;
//            qDebug()<<"continue"<<continue_;
//            continue_ = false;
//            qDebug()<<"x"<<mouseEvent->x();
            preframe_mouse_x = mouse_x;
//            qDebug()<<"pre_x"<<preframe_mouse_x;
            previewFrame.m_run = 2;
            m_pTimer->stop();
//            this->preframe_mouse_x = mouse_x;
            m_pTimer->start(1000);
//            continue_ = false;
//            if(continue_ == false)
//                return false;
//            qDebug()<<"continue"<<continue_;
//            qint64 position = mouse_x*ui->horizontalSlider->maximum()/ui->horizontalSlider->width();
//            qDebug()<<"pos"<<transfer_to_std_time(position);
//            this->pause_time = position;
//            ui->label_4->move(mouse_x+ui->horizontalSlider->x(),ui->horizontalSlider->y()-ui->label_4->height());
//            ui->label_4->setPixmap(QPixmap("D:\\images\\72.jpg"));
//            previewFrame.time = position / 1000;
//    //        previewFrame.time = 60;
//            previewFrame.filename = this->playList[this->current_index];
////            while(continue_ == false && previewFrame.m_run !=0){
////                qDebug()<<"出不去";
////            }
//            previewFrame.start();
//            ui->label_4->setScaledContents(true);
//            ui->label_4->setVisible(true);
        }
        if (e->type() == QEvent::MouseButtonPress && ui->toolButton_8->text() == "倒放"){

            if(mouseEvent->button()  == Qt::LeftButton){
//                qDebug()<<"m_x"<<mouse_x;
//                qDebug()<<"m_y"<<mouse_y;
//                qDebug()<<"slider_x"<<ui->horizontalSlider->x();
//                qDebug()<<"slider_y"<<ui->horizontalSlider->y();
    //           qDebug()<<mouse_x;
    //           qDebug()<<ui->horizontalSlider->width();
    //           qDebug()<<ui->horizontalSlider->maximum();

                 qint64 position = mouseEvent->x()*ui->horizontalSlider->maximum()/ui->horizontalSlider->width();
               qDebug()<<position;
    //           ui->horizontalSlider->setValue(position);
                 setPosition(position);
    //           emit mousePress(e);
    //           QPixmap pixmap(":/images/all.jpg");
    //           QPalette palette;
    //           palette.setBrush(backgroundRole(),QBrush(pixmap));
    //           ui->horizontalSlider->setPalette(palette);
            }
        }
//        if(e->type() == QEvent::HoverEnter){
//            qDebug()<<"进入悬停";
//            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e);

//            qDebug()<<"slider_x"<<ui->horizontalSlider->x();
//            qDebug()<<"x"<<mouse_x;
//            if (this->current_index != -1){
//            qint64 position = (mouse_x-ui->horizontalSlider->x())*ui->horizontalSlider->maximum()/ui->horizontalSlider->width();
//            this->pause_time = position;
//            ui->label_4->move(mouse_x,ui->label_4->y());
//            ui->label_4->setPixmap(QPixmap("D:\\images\\72.jpg"));
//            previewFrame.time = position / 1000;
//            previewFrame.filename = this->playList[this->current_index];
//            previewFrame.start();
//            ui->label_4->setScaledContents(true);
//            ui->label_4->setVisible(true);
//            VideoSurface * videoSurface = new VideoSurface();
//        }
//    }
    }


    if(obj==ui->horizontalSlider_2)
    {
        if (e->type()==QEvent::MouseButtonRelease && ui->toolButton_8->text() == "停止倒放") //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(e);
            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
                int mouse_x = mouseEvent->x();
   //           qDebug()<<mouse_x;
   //           qDebug()<<ui->horizontalSlider->width();
   //           qDebug()<<ui->horizontalSlider->maximum();


//                qint64 ori_position = ui->horizontalSlider_2->value();
                qint64 position = mouse_x*ui->horizontalSlider_2->maximum()/ui->horizontalSlider_2->width();
//                qDebug()<<"Pos位"<<position;
                if(position != ui->horizontalSlider_2->value()){
                    if(this->type == VIDEO && ui->widget_2->type == 1){
                        if(DecodeWork.GetSate() != 2){
                            QMessageBox::warning(this, tr("Error"),
                                                           tr("请先暂停再调节")
                                                           );
                        }
                        else{
                            for(int i=0;i<100;i++){
                                int j =1;
                            }
        //                    DecodeWork.PausePlay();
        //                    DecodeWorkAudio.PausePlay();
                            ui->horizontalSlider_2->setValue(position);
                            DecodeWork.SetSeekPos(position);
                            DecodeWorkAudio.setVideoTime(position);
                            DecodeWorkAudio.SetSeekPos(position);

                        }
                    }

                    if(this->type == VIDEO && ui->widget_2->type == 0){
                        if(DecodeWorkAudio.GetSate() != 2){
                            QMessageBox::warning(this, tr("Error"),
                                                           tr("请先暂停再调节")
                                                           );
                        }
                        else{
                            for(int i=0;i<100;i++){
                                int j =1;
                            }
        //                    DecodeWork.PausePlay();
        //                    DecodeWorkAudio.PausePlay();
                            ui->horizontalSlider_2->setValue(position);
//                            DecodeWork.SetSeekPos(position);
                            DecodeWorkAudio.SetSeekPos(position);

                        }
                    }

                    if(this->type == AUDIO){
                        if(DecodeWorkAudio.GetSate() != 2){
                            QMessageBox::warning(this, tr("Error"),
                                                           tr("请先暂停再调节")
                                                           );
                        }
                        else{
                            for(int i=0;i<100;i++){
                                int j =1;
                            }
                            qDebug()<<"改变pos";
                            ui->horizontalSlider_2->setValue(position);
        //                    DecodeWorkAudio.PausePlay();
                            DecodeWorkAudio.SetSeekPos(position);

                        }
                    }
                }


            }
        }

}
    return QWidget::eventFilter(obj,e);
}

//void MainWindow::presentframe(const QVideoFrame & frame){
//    if (frame.endTime() == this->pause_time){
//        qDebug()<<"present frame";
//        QVideoFrame frametodraw(frame);
//        if(!frametodraw.map(QAbstractVideoBuffer::ReadOnly))
//            return;
//        QImage img = QImage(frame.bits(),
//                    frame.width(),
//                    frame.height(),
//                    frame.bytesPerLine(),
//                    QVideoFrame::imageFormatFromPixelFormat(frametodraw.pixelFormat())
//                    //QImage::Format_RGB32
//                    );
//        img = img.mirrored(false, true);//图像垂直翻转(图像是倒置的，调用该函数可正置。同时该函数也解决了频繁的内存错误引起的崩溃, 原因不明)
//        qDebug()<<img.size();
//        img.save(QString("D:/images/001.jpg"), "JPG");
//        //这里可以分析或编辑图像后再输出显示视频
//        //视频的显示则利用重写paintEvent()函数来绘制实现。还可以直接将图像设置到label控件中，也会形成视频。
//        update();                       //通知Qt重绘

//        frametodraw.unmap();
//    }


//}

void MainWindow::back(){
    qint64 old_position = this->mediaplayer->position();
    qint64 new_position = old_position - 1000;
    if (new_position < 0){
        return;
    }
    setPosition(new_position);
}

void MainWindow::forward(){
    qint64 old_position = this->mediaplayer->position();
    qint64 new_position = old_position + 1000;
    if (new_position > this->mediaplayer->duration()){
        return;
    }
    setPosition(new_position);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    QString key_info = QKeySequence(e->modifiers() + e->key()).toString();
    qDebug()<<key_info;
    if (this->current_index == -1 || this->notkey){
        return;
    }
    if (key_info == "Space"){
        qDebug()<<111111111111;
        this->play();
    }
    if (key_info == "Down"){
        getNextAccessible(this->current_index+1);
    }
    if (key_info == "Up"){
        getPreviousAccessible(this->current_index-1);
    }
    if (key_info=="Left"){
        back();
    }
    if (key_info == "Right"){
        forward();
    }
}

void MainWindow::on_toolButton_5_clicked()
{
    back();
}

void MainWindow::on_toolButton_6_clicked()
{
    forward();
}

void MainWindow::on_toolButton_7_clicked()
{
    if (ui->toolButton_7->toolTip()=="单曲循环"){
        ui->toolButton_7->setToolTip("顺序播放");
        ui->toolButton_7->setIcon(QPixmap(":/images/series.jpg"));
    }
    else{
        ui->toolButton_7->setToolTip("单曲循环");
        ui->toolButton_7->setIcon(QPixmap(":/images/recurrent.jpg"));
    }

}

void MainWindow::on_toolButton_8_clicked()
{   if (ui->toolButton_8->text() == "倒放"){
        if(this->current_index == -1){
            return;
        }

        ui->listWidget->setEnabled(false);
        ui->toolButton_2->setEnabled(false);
        this->last_begin_to_reverse = this->mediaplayer->position();
        this->file_reverse = this->playList[this->current_index];
        QString filename = this->playList[this->current_index];
        this->reverse_duration = ui->horizontalSlider->maximum();
        this->mediaplayer->setMedia(QUrl::fromLocalFile(""));
        this->play();

        ui->widget->setVisible(false);
        this->current_index = -1;
        qDebug()<<"在这测试一次";
        ui->toolButton_8->setText("停止倒放");

        ui->toolButton->setVisible(false);
        ui->horizontalSlider->setVisible(false);
        ui->toolButton_9->setVisible(true);
        ui->horizontalSlider_2->setVisible(true);
        ui->toolButton_5->setVisible(false);
        ui->toolButton_6->setVisible(false);
        ui->comboBox->setEnabled(false);
        ui->toolButton_7->setEnabled(false);
//        QString duration_str = ui->label->text();
        ui->label->setVisible(false);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(true);
        ui->label_6->setVisible(true);
        ui->label_7->setVisible(true);
        ui->label_6->setText(transfer_to_std_time(reverse_duration));
        if(type == AUDIO){
            ui->widget_2->setVisible(false);
            ui->widget_3->setVisible(false);
            DecodeWorkAudio.SetSate(0);
//            DecodeWorkAudio.no_video_signal = true;
//            DecodeWork.SetSate(0);





//            DecodeWork.quit();
//            DecodeWork.wait();
//            DecodeWorkAudio.quit();
//            DecodeWorkAudio.wait();

            ui->toolButton_9->setToolTip("暂停");
            ui->toolButton_9->setIcon(QPixmap(":/images/pause.png"));
//            DecodeWork.SetSate(1);
            DecodeWorkAudio.SetSate(1);

            DecodeWork.LoadVideoFile(filename);
            DecodeWorkAudio.LoadVideoFile(filename);
            reverse_duration=DecodeWorkAudio.GetDuration(); //获取总时间
            ui->horizontalSlider_2->setMaximum(reverse_duration);  //设置最大值
            ui->horizontalSlider_2->setMinimum(0); //设置最小值
            ui->horizontalSlider_2->setValue(reverse_duration);
//            DecodeWork.SetSeekPos(ui->horizontalSlider_2->maximum());
//            DecodeWork.video_pack.clear();
//            DecodeWork.over_pack.clear();
            DecodeWorkAudio.audio_pack.clear();
            DecodeWorkAudio.over_pack.clear();

//            DecodeWork.start();
            DecodeWorkAudio.SetSeekPos(ui->horizontalSlider_2->maximum());

            DecodeWorkAudio.start();
        }
        if(type == VIDEO){
//            if(ui->widget_2->type == 1){
//            ui->widget_2->src_mImage = QImage();
            ui->widget_2->mImage = QImage();
            ui->widget_2->setVisible(true);
            ui->widget_3->setVisible(false);
            DecodeWorkAudio.no_video_signal = false;
            DecodeWork.SetSate(0);
            DecodeWorkAudio.SetSate(0);




//            DecodeWork.quit();
//            DecodeWork.wait();
//            DecodeWorkAudio.quit();
//            DecodeWorkAudio.wait();

            ui->toolButton_9->setToolTip("暂停");
            ui->toolButton_9->setIcon(QPixmap(":/images/pause.png"));


            DecodeWork.LoadVideoFile(filename);
//            qDebug()<<"凯斯到了0";
            DecodeWorkAudio.LoadVideoFile(filename);
//            qDebug()<<"凯斯到了";
            DecodeWork.SetSate(1);
            DecodeWorkAudio.SetSate(1);
            reverse_duration=DecodeWork.GetDuration(); //获取总时间
            ui->horizontalSlider_2->setMaximum(reverse_duration);  //设置最大值
            ui->horizontalSlider_2->setMinimum(0); //设置最小值
            ui->horizontalSlider_2->setValue(reverse_duration);
            DecodeWork.video_pack.clear();
            DecodeWork.over_pack.clear();

            DecodeWorkAudio.audio_pack.clear();
            DecodeWorkAudio.over_pack.clear();
            qDebug()<<"max——duration"<<ui->horizontalSlider_2->maximum();
            DecodeWork.SetSeekPos(ui->horizontalSlider_2->maximum());
            DecodeWork.start();
            DecodeWorkAudio.setVideoTime(ui->horizontalSlider_2->maximum());
            DecodeWorkAudio.SetSeekPos(ui->horizontalSlider_2->maximum());
            DecodeWorkAudio.start();
//            }
        }

        qDebug()<<"主线程";
//        DecodeWork.exit();
//        while(DecodeWork.finished == false){
//            ;
//        }

        this->isReverse = true;

    }
    else{

        ui->listWidget->setEnabled(true);
        ui->toolButton_2->setEnabled(true);
        ui->toolButton_5->setVisible(true);
        ui->toolButton_6->setVisible(true);
        ui->comboBox->setEnabled(true);
        ui->toolButton_7->setEnabled(true);
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);

        ui->label_3->setVisible(true);
//        ui->label_4->setVisible(true);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);
        ui->label_7->setVisible(false);
        if(type == AUDIO){
//            DecodeWork.StopPlay();
            DecodeWorkAudio.StopPlay();
//            audio_mutex.unlock();
//            DecodeWorkAudio.audio_pack.clear();
//            DecodeWork.over_pack.clear();
        }
        if(type == VIDEO){
//            if(ui->widget_2->type==1){
            DecodeWork.StopPlay();
            DecodeWorkAudio.StopPlay();
//            }
//            if(ui->widget_2->type==0){
//                DecodeWorkAudio.StopPlay();
//            }
//            video_mutex.unlock();
//            audio_mutex.unlock();
//            DecodeWork.video_pack.clear();
//            DecodeWorkAudio.over_pack.clear();
//            DecodeWorkAudio.audio_pack.clear();
//            DecodeWork.over_pack.clear();
        }

       ui->toolButton_8->setText("倒放");
       ui->horizontalSlider->setVisible(true);
       ui->horizontalSlider_2->setVisible(false);
       ui->toolButton->setVisible(true);
       ui->toolButton_9->setVisible(false);
       ui->horizontalSlider->setMaximum(100);  //设置最大值
       ui->horizontalSlider->setMinimum(0); //设置最小值
       ui->horizontalSlider->setValue(0);
       this->mediaplayer->setMedia(QUrl::fromLocalFile(this->file_reverse));
//       doBeforeChangeMedia(this->file_reverse);
       qDebug()<<"倒放后的状态"<<mediaplayer->state();

       this->play();
       setPosition(this->last_begin_to_reverse);

       if(type == AUDIO){
           //           ui->widget_2->setVisible(false);

            if(dontshow == false)
            ui->widget_3->setVisible(true);
       }
       if(type == VIDEO){
           ui->widget_2->setVisible(false);
           ui->widget->setVisible(true);
       }
//       qDebug()<<"file_reverse"<<file_reverse;
       this->current_index = this->playList.indexOf(file_reverse);
//       doBeforeChangeMedia(this->file_reverse);


//       this->play();
       qDebug()<<"此时的current index"<<current_index;
       this->isReverse = false;
//       DecodeWork.StopPlay();
       zero_tolerence = 0;

    }
}

void MainWindow::on_verticalSlider_sliderMoved(int position)
{
    this->mediaplayer->setVolume(position);
    ui->widget_2->volumn = (double)(1.5*position)/100.0;
}

void MainWindow::slotGetCurrentTime(qint64 pts){
//       qDebug()<<11111111;

        qDebug()<<"pts:"<<pts;


        ui->horizontalSlider_2->setValue(pts);

//        video_mutex = true;
//        audio_mutex = true;


        ui->label_5->setText(transfer_to_std_time(pts));

//        if(type == VIDEO){
//            qDebug()<<"放开video了";
//            video_mutex.unlock();
//        }
//        if(type == AUDIO){
//            audio_mutex.unlock();
//        }

//        if (pts == 0){
//            DecodeWork.StopPlay();
//            DecodeWorkAudio.StopPlay();
//            QMessageBox::warning(this, tr("Error"),
//                                           tr("倒放结束")
//                                           );
//        }

//        ui->label_duration->setText(QString("%1/%2").arg(pts).arg(duration));
}



void MainWindow::on_toolButton_9_clicked()
{

    if(type == VIDEO && ui->widget_2->type == 1){
    if (DecodeWork.GetSate() == 2){


        ui->toolButton_9->setToolTip("倒放暂停");
        ui->toolButton_9->setIcon(QPixmap(":/images/pause.png"));
        DecodeWork.SetSate(1);

    }
    else if(DecodeWork.GetSate() == 1)
    {
        ui->toolButton_9->setToolTip("倒放播放");
        ui->toolButton_9->setIcon(QPixmap(":/images/play.png"));
        DecodeWork.SetSate(2);
    }

    if (DecodeWorkAudio.GetSate() == 2){


//        ui->toolButton_9->setToolTip("暂停");
//        ui->toolButton_9->setIcon(QPixmap(":/images/pause.png"));
        DecodeWorkAudio.SetSate(1);


    }
    else if(DecodeWorkAudio.GetSate() == 1)
    {
//        ui->toolButton_9->setToolTip("播放");
//        ui->toolButton_9->setIcon(QPixmap(":/images/play.png"));
        DecodeWorkAudio.SetSate(2);
    }
    }

    if(type == VIDEO && ui->widget_2->type == 0){
    if (DecodeWorkAudio.GetSate() == 2){


        ui->toolButton_9->setToolTip("倒放暂停");
        ui->toolButton_9->setIcon(QPixmap(":/images/pause.png"));
        DecodeWorkAudio.SetSate(1);

    }
    else if(DecodeWorkAudio.GetSate() == 1)
    {
        ui->toolButton_9->setToolTip("倒放播放");
        ui->toolButton_9->setIcon(QPixmap(":/images/play.png"));
        DecodeWorkAudio.SetSate(2);
    }

    if (DecodeWork.GetSate() == 2){


//        ui->toolButton_9->setToolTip("暂停");
//        ui->toolButton_9->setIcon(QPixmap(":/images/pause.png"));
        DecodeWork.SetSate(1);


    }
    else if(DecodeWork.GetSate() == 1)
    {
//        ui->toolButton_9->setToolTip("播放");
//        ui->toolButton_9->setIcon(QPixmap(":/images/play.png"));
        DecodeWork.SetSate(2);
    }
    }

    if(type == AUDIO){
    if (DecodeWorkAudio.GetSate() == 2){


        ui->toolButton_9->setToolTip("倒放暂停");
        ui->toolButton_9->setIcon(QPixmap(":/images/pause.png"));
        DecodeWorkAudio.SetSate(1);
        qDebug()<<"开始古可11111";

    }
    else if(DecodeWorkAudio.GetSate() == 1)
    {
        ui->toolButton_9->setToolTip("倒放播放");
        ui->toolButton_9->setIcon(QPixmap(":/images/play.png"));
        DecodeWorkAudio.SetSate(2);
        qDebug()<<"开始古可11111";
    }
    }
}

void MainWindow::on_listWidget_currentTextChanged(const QString &currentText)
{

}

void MainWindow::threadFinished(){
    qDebug()<<"finished";
    if ((this->type == VIDEO) && (ui->widget_2->type == 1) && (DecodeWork.GetSate() == 0 || DecodeWorkAudio.GetSate() == 0)){
        qDebug()<<"case1";
        return;
    }
    if ((this->type == VIDEO) && (ui->widget_2->type == 0) && (DecodeWorkAudio.GetSate() == 0)){
        qDebug()<<"case8";
        DecodeWork.StopPlay();
        return;
    }

    if(this->type == AUDIO && (DecodeWorkAudio.GetSate() == 0)){
        qDebug()<<"vase23";
        return;
    }
    if((this->type == VIDEO) && (ui->widget_2->type == 1) && (DecodeWork.finished == false || DecodeWorkAudio.finished == false)){
        qDebug()<<"case2";
        return;

    }

    if((this->type == VIDEO) && (ui->widget_2->type == 0) && (DecodeWorkAudio.finished == false)){
        qDebug()<<"case7";
        return;

    }


    if((this->type == AUDIO) && DecodeWorkAudio.finished == false){
                qDebug()<<"case4";
        return;

    }
//    if((this->type == AUDIO) && DecodeWorkAudio.finished == false){
//        qDebug()<<"返回了";
//        return;

//    }
//    DecodeWorkAudio.no_video_signal =false;


    if(this->type == VIDEO){
//        if(ui->widget_2->type == 1){
    DecodeWork.SetSate(0);
    DecodeWorkAudio.SetSate(0);




//    DecodeWork.quit();
//    DecodeWork.wait();
//    DecodeWorkAudio.quit();
//    DecodeWorkAudio.wait();
    DecodeWork.finished = false;
    DecodeWorkAudio.finished = false;
    qDebug()<<"restart video";
    ui->toolButton_9->setToolTip("暂停");
    ui->toolButton_9->setIcon(QPixmap(":/images/pause.png"));


//    DecodeWork.LoadVideoFile(this->file_reverse);
//    DecodeWorkAudio.LoadVideoFile(this->file_reverse);
    qDebug()<<"还好把";
    reverse_duration=DecodeWork.GetDuration(); //获取总时间
    ui->horizontalSlider_2->setMaximum(reverse_duration);  //设置最大值
    ui->horizontalSlider_2->setMinimum(0); //设置最小值
    ui->horizontalSlider_2->setValue(reverse_duration);
    DecodeWork.SetSeekPos(ui->horizontalSlider_2->maximum());
    DecodeWorkAudio.setVideoTime(ui->horizontalSlider_2->maximum());
    DecodeWorkAudio.SetSeekPos(ui->horizontalSlider_2->maximum());
    DecodeWork.video_pack.clear();
    DecodeWork.over_pack.clear();
    DecodeWorkAudio.audio_pack.clear();
    DecodeWorkAudio.over_pack.clear();
    DecodeWork.SetSate(1);
    DecodeWorkAudio.SetSate(1);
    DecodeWork.start();
    DecodeWorkAudio.start();
//        }
    }

    if(this->type == AUDIO){
//    DecodeWork.SetSate(0);
    DecodeWorkAudio.SetSate(0);
//    DecodeWork.finished = false;




//    DecodeWork.quit();
//    DecodeWork.wait();
    DecodeWorkAudio.quit();
    DecodeWorkAudio.wait();
    DecodeWorkAudio.finished = false;
    qDebug()<<"restart audio";
    ui->toolButton_9->setToolTip("暂停");
    ui->toolButton_9->setIcon(QPixmap(":/images/pause.png"));
//    DecodeWork.SetSate(1);
    DecodeWorkAudio.SetSate(1);

//    DecodeWork.LoadVideoFile(this->file_reverse);
    DecodeWorkAudio.LoadVideoFile(this->file_reverse);
    reverse_duration=DecodeWorkAudio.GetDuration(); //获取总时间
    ui->horizontalSlider_2->setMaximum(reverse_duration);  //设置最大值
    ui->horizontalSlider_2->setMinimum(0); //设置最小值
    ui->horizontalSlider_2->setValue(reverse_duration);
//    DecodeWork.SetSeekPos(ui->horizontalSlider_2->maximum());
    DecodeWorkAudio.SetSeekPos(ui->horizontalSlider_2->maximum());
//    DecodeWork.video_pack.clear();
//    DecodeWork.over_pack.clear();
    DecodeWorkAudio.audio_pack.clear();
    DecodeWorkAudio.over_pack.clear();
//    DecodeWork.start();
    DecodeWorkAudio.start();
    }
}





void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{



////    ui->horizontalSlider_2->setValue(position);

////    DecodeWork.SetSeekPos(position);
////    qint64 position = mouse_x*ui->horizontalSlider_2->maximum()/ui->horizontalSlider_2->width();
//    if(position != ui->horizontalSlider_2->value()){
//        if(this->type == VIDEO){
//            if(DecodeWork.GetSate() != 2){
//                QMessageBox::warning(this, tr("Error"),
//                                               tr("请先暂停再调节")
//                                               );
//            }
//            else{
////                    DecodeWork.PausePlay();
////                    DecodeWorkAudio.PausePlay();
//                ui->horizontalSlider_2->setValue(position);
//                DecodeWork.SetSeekPos(position);
//                DecodeWorkAudio.SetSeekPos(position);

//            }
//        }
//        if(this->type == AUDIO){
//            if(DecodeWork.GetSate() != 2){
//                QMessageBox::warning(this, tr("Error"),
//                                               tr("请先暂停再调节")
//                                               );
//            }
//            else{
//                qDebug()<<"改变pos";
//                ui->horizontalSlider_2->setValue(position);
////                    DecodeWorkAudio.PausePlay();
//                DecodeWorkAudio.SetSeekPos(position);

//            }
//        }
//    }
}




void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
//    qDebug()<<"slider value:"<<value;
//    if(value < 10){
//        qDebug()<<"1你们1";
//    }
}


int MainWindow::openCodecContext(const AVFormatContext* pFormatCtx, int* pStreamIndex, enum AVMediaType type, AVCodecContext** ppCodecCtx) {
    qDebug()<<"222222222";
    int streamIdx = -1;
    // 获取流下标
    for (int i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == type) {
            streamIdx = i;
            break;
        }
    }
    if (streamIdx == -1) {
        qDebug()<<("find video stream failed!\n");
        exit(-1);
    }
    // 寻找解码器
    AVCodecContext* pCodecCtx = pFormatCtx->streams[streamIdx]->codec;
    AVCodec* pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (NULL == pCodec) {
        qDebug()<<("avcode find decoder failed!\n");
        exit(-1);
    }

    //打开解码器
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        qDebug()<<("avcode open failed!\n");
        exit(-1);
    }
    *ppCodecCtx = pCodecCtx;
    *pStreamIndex = streamIdx;

    qDebug()<<"OK";
    return 0;
}

void MainWindow::ffmpegtest(double timestamp){
//    int i = 0;
////    qDebug()<<"见来了";
//        AVFormatContext* pInFormatCtx = NULL;
//        AVCodecContext* pVideoCodecCtx = NULL;
//        AVCodecContext* pAudioCodecCtx = NULL;
//        AVPacket* pPacket = NULL;
//        AVFrame* pFrame = NULL;
//        AVFrame* pFrameRGB = NULL;
//        int ret;
//        /* 支持本地文件和网络url */
//        const char streamUrl[] = "D:/qtproject/Video_Player/video_test/t113.mp4";

//        /* 1. 注册 */
//        av_register_all();

//        pInFormatCtx = avformat_alloc_context();

//        /* 2. 打开流 */
//        if (avformat_open_input(&pInFormatCtx, streamUrl, NULL, NULL) != 0) {
//            qDebug()<<("Couldn't open input stream.\n");
//            return;
//        }

//        /* 3. 获取流的信息 */
//        if (avformat_find_stream_info(pInFormatCtx, NULL) < 0) {
//            qDebug()<<("Couldn't find stream information.\n");
//            return;
//        }

//        int videoStreamIdx = -1;
//        int audioStreamIdx = -1;
//        /* 4. 寻找并打开解码器 */

//        openCodecContext(pInFormatCtx, &videoStreamIdx, AVMEDIA_TYPE_VIDEO, &pVideoCodecCtx);
//        openCodecContext(pInFormatCtx, &audioStreamIdx, AVMEDIA_TYPE_AUDIO, &pAudioCodecCtx);

////        qDebug()<<ui->horizontalSlider->value();
////        qDebug()<<videoStreamIdx;
//        qDebug()<<"帧率为"<<pInFormatCtx->streams[videoStreamIdx]->avg_frame_rate.num/pInFormatCtx->streams[videoStreamIdx]->avg_frame_rate.den;



//        pPacket = av_packet_alloc();
//        pFrame = av_frame_alloc();
//        pFrameRGB = av_frame_alloc();


//        int numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, pVideoCodecCtx->width, pVideoCodecCtx->height);
//        uint8_t* buffer = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));

//        avpicture_fill((AVPicture*)pFrameRGB, buffer, AV_PIX_FMT_RGB24, pVideoCodecCtx->width, pVideoCodecCtx->height);

//        struct SwsContext* img_convert_ctx;
//        img_convert_ctx = sws_getContext(pVideoCodecCtx->width, pVideoCodecCtx->height, pVideoCodecCtx->pix_fmt,
//                pVideoCodecCtx->width, pVideoCodecCtx->height, AV_PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);


////        av_seek_frame(pInFormatCtx, -1,	timestamp*AV_TIME_BASE,AVSEEK_FLAG_BACKWARD);
//        while(av_read_frame(pInFormatCtx, pPacket)>=0){
//        if (pPacket->stream_index == videoStreamIdx){
//            avcodec_decode_video2(pVideoCodecCtx, pFrame, &ret, pPacket);
//            if(ret){
//                int video_width = pVideoCodecCtx->width;
//                int video_height = pVideoCodecCtx->height;
//                qDebug()<<video_width;
//                qDebug()<<video_height;
//                sws_scale(img_convert_ctx, pFrame->data, pFrame->linesize, 0, pVideoCodecCtx->height,
//                                    pFrameRGB->data, pFrameRGB->linesize);
//                QImage image(pFrameRGB->data[0], pVideoCodecCtx->width, pVideoCodecCtx->height, pFrameRGB->linesize[0], QImage::Format_RGB888);
//                image.save("D:\\0.jpg");

//            //将解码后的YUV数据转换成RGB24
////            img_convert_ctx = sws_getContext(video_width, video_height,
////                pInFormatCtx->streams[videoStreamIdx]->codec->pix_fmt, video_width, video_height,
////                AV_PIX_FMT_RGB24, SWS_BICUBIC, nullptr, nullptr, nullptr);

////            //计算RGB图像所占字节大小
////            int numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, video_width, video_height);

////            //申请空间存放RGB图像数据
////            uint8_t * out_buffer_rgb = (uint8_t *)av_malloc(numBytes * sizeof(uint8_t));
////            sws_scale(img_convert_ctx,
////                (uint8_t const **)
////                      pFrame->data,
////                pFrame->linesize, 0, video_height, pFrameRGB->data,
////                pFrameRGB->linesize);

////            //加载图片数据
////            QImage image(out_buffer_rgb, video_width, video_height, QImage::Format_RGB888);

////            qDebug()<<image.size();
////            image.save("D:/0.jpg");
//            }
//        }
//        av_free_packet(pPacket);
//}
//            av_frame_free(&pFrame);
//            avcodec_close(pVideoCodecCtx);
//            avcodec_close(pAudioCodecCtx);
//            avformat_close_input(&pInFormatCtx);







////        int cnt = 20; // 读取20帧数据（音频和视频）
////        while (cnt--) {
////            /* 5. 读流数据, 未解码的数据存放于pPacket */
////            ret = av_read_frame(pInFormatCtx, pPacket);
////            qDebug()<<ret;
////            if (ret < 0) {
////                qDebug()<<("av_read_frame error\n");
////                break;
////            }

////            /* 6. 解码, 解码后的数据存放于pFrame */
////            /* 视频解码 */
////            if (pPacket->stream_index == videoStreamIdx) {
//////                qDebug()<<"video";
////                avcodec_decode_video2(pVideoCodecCtx, pFrame, &ret, pPacket);
//////                qDebug()<<"ret"<<ret;
////                if (ret == 0) {
////                    qDebug()<<("video decodec error!\n");
////                    continue;
////                }
////                qDebug()<<("* * * * * * video * * * * * * * * *\n");
////                qDebug()<<("___height: [%d]\n", pFrame->height);
////                qDebug()<<("____width: [%d]\n", pFrame->width);
////                qDebug()<<("pict_type: [%d]\n", pFrame->pict_type);
////                qDebug()<<("key_frame: [%d]\n", pFrame->key_frame); // 视频关键帧  1 -> 是 0 -> 否
////                qDebug()<<("___format: [%d]\n", pFrame->format);
////                qDebug()<<("* * * * * * * * * * * * * * * * * * *\n\n");
////            }

////            /* 音频解码 */
////            if (pPacket->stream_index == audioStreamIdx) {
////                qDebug()<<"audio";
////                avcodec_decode_audio4(pAudioCodecCtx, pFrame, &ret, pPacket);
////                if (ret < 0) {
////                    qDebug()<<("audio decodec error!\n");
////                    continue;
////                }
////                qDebug()<<("* * * * * * audio * * * * * * * * * *\n");
////                qDebug()<<("____nb_samples: [%d]\n", pFrame->nb_samples);
////                qDebug()<<("__samples_rate: [%d]\n", pFrame->sample_rate);
////                qDebug()<<("channel_layout: [%lu]\n", pFrame->channel_layout);
////                qDebug()<<("________format: [%d]\n", pFrame->format);
////                qDebug()<<("* * * * * * * * * * * * * * * * * * *\n\n");
////            }
////            av_packet_unref(pPacket); /* 将缓存空间的引用计数-1，并将Packet中的其他字段设为初始值。如果引用计数为0，自动的释放缓存空间 */
////        }
////        /* 释放资源 */
////        av_frame_free(&pFrame);
////        av_packet_free(&pPacket);
////        avcodec_close(pVideoCodecCtx);
////        avcodec_close(pAudioCodecCtx);
////        avformat_close_input(&pInFormatCtx);

//        return;


    AVFormatContext *pFormatCtx = avformat_alloc_context();
    int res;
    res = avformat_open_input(&pFormatCtx, "D:\\qtproject\\Video_Player\\video_test\\t113.mp4", nullptr, nullptr);
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
        qDebug()<<(stderr, "Unsupported codec!\n");
        return; // Codec not found
    }
    AVCodecContext *pCodecCtx = nullptr;
    // Copy context
    pCodecCtx = avcodec_alloc_context3(pCodec);
    if(avcodec_copy_context(pCodecCtx, pCodecCtxOrig) != 0) {
        qDebug()<<(stderr, "Couldn't copy codec context");
        return; // Error copying codec context
    }
    // Open codec
    if(avcodec_open2(pCodecCtx, pCodec, nullptr)<0) {
        return;// Could not open codec
    }
    AVFrame *pFrameRGB = nullptr;
    pFrameRGB = av_frame_alloc();
    res = av_seek_frame(pFormatCtx, -1, timestamp * AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);
    if (res<0) {
        return;
    }
    AVPacket packet;
    while(av_read_frame(pFormatCtx, &packet) >= 0) {
//        av_read_frame(pFormatCtx, &packet);
        if(packet.stream_index == videoStream) {
            res = avcodec_send_packet(pCodecCtx, &packet);
            int gotPicture = avcodec_receive_frame(pCodecCtx, pFrameRGB); //gotPicture = 0 success, a frame was returned
            if(gotPicture == 0) {
                SwsContext* swsContext = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24,
                                          SWS_BICUBIC, nullptr, nullptr, nullptr);
                AVFrame* frameRGB = av_frame_alloc();
                avpicture_alloc((AVPicture*)frameRGB, AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);
                sws_scale(swsContext, pFrameRGB->data, pFrameRGB->linesize, 0, pCodecCtx->height, frameRGB->data, frameRGB->linesize);
                QImage image(frameRGB->data[0], pCodecCtx->width, pCodecCtx->height, frameRGB->linesize[0], QImage::Format_RGB888);
                image.save("D:\\0.jpg");
                avformat_close_input(&pFormatCtx);
                return;
            }
        }
    }
    return ;


}

void MainWindow::setPreviewFrame(QImage image){
    qDebug()<<"发了";
    qDebug()<<image.size();
    if(this->isFullScreen == true && ui->toolButton->isVisible() == false)return;
//    image = image.scaled(ui->label_4->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

//    /*ui->label_4->move(ui->horizontalSlider->width()*((double)(previewFrame.time*1000)/(double)ui->horizontalSlider->max*/imum())+ui->horizontalSlider->x(),ui->horizontalSlider->y()-ui->label_4->height());
//    ui->label_4->setScaledContents(true);
//    pre_frame_mutex.lock();
    ui->label_4->setVisible(true);
    ui->label_4->setPixmap(QPixmap::fromImage(image));
    qDebug()<<"painter 结束了";
//    pre_frame_mutex.unlock();
//    previewFrame.m_run = 2;
//    m_pTimer->stop();
}

void MainWindow::parseWVV(){
    ui->widget->setVisible(false);
    ui->widget_3->setVisible(true);
    QFile fileInfo("D:/qtproject/Video_Player/video_test/123.wav");
    if (!fileInfo.open(QIODevice::ReadOnly))
    {
        return ;
    }
    fileInfo.read(WavFileHeader.RiffName, sizeof(WavFileHeader.RiffName));
    fileInfo.read((char*)&WavFileHeader.nRiffLength, sizeof(WavFileHeader.nRiffLength));
    fileInfo.read(WavFileHeader.WavName, sizeof(WavFileHeader.WavName));
    fileInfo.read(WavFileHeader.FmtName, sizeof(WavFileHeader.FmtName));
    fileInfo.read((char*)&WavFileHeader.nFmtLength, sizeof(WavFileHeader.nFmtLength));
    fileInfo.read((char*)&WavFileHeader.nAudioFormat, sizeof(WavFileHeader.nAudioFormat));
    fileInfo.read((char*)&WavFileHeader.nChannleNumber, sizeof(WavFileHeader.nChannleNumber));
    fileInfo.read((char*)&WavFileHeader.nSampleRate, sizeof(WavFileHeader.nSampleRate));
    fileInfo.read((char*)&WavFileHeader.nBytesPerSecond, sizeof(WavFileHeader.nBytesPerSecond));
    fileInfo.read((char*)&WavFileHeader.nBytesPerSample, sizeof(WavFileHeader.nBytesPerSample));
    fileInfo.read((char*)&WavFileHeader.nBitsPerSample, sizeof(WavFileHeader.nBitsPerSample));

    QString strAppendMessageData;
    if (WavFileHeader.nFmtLength >= 18)
    {
        fileInfo.read((char*)&WavFileHeader.nAppendMessage, sizeof(WavFileHeader.nAppendMessage));

        int appendMessageLength = WavFileHeader.nFmtLength - 18;
        WavFileHeader.AppendMessageData = new char[appendMessageLength];
        fileInfo.read(WavFileHeader.AppendMessageData, appendMessageLength);
        strAppendMessageData = QString(WavFileHeader.AppendMessageData);
    }
    char chunkName[5];
    fileInfo.read(chunkName, sizeof(chunkName) - 1);
    chunkName[4] = '\0';
    QString strChunkName(chunkName);
    if (strChunkName.compare("fact") == 0)
    {
        strcpy(WavFileHeader.FactName, chunkName);
        fileInfo.read((char*)&WavFileHeader.nFactLength, sizeof(WavFileHeader.nFactLength));
        fileInfo.read(WavFileHeader.FactData, sizeof(WavFileHeader.FactData));
        fileInfo.read(WavFileHeader.DATANAME, sizeof(WavFileHeader.DATANAME));
    }
    else
    {
        strcpy(WavFileHeader.DATANAME, chunkName);
    }

    fileInfo.read((char*)&WavFileHeader.nDataLength, sizeof(WavFileHeader.nDataLength));

    QByteArray pcmData;
    pcmData = fileInfo.readAll();
    WavFileHeader.fileDataSize = pcmData.size();
    WavFileHeader.fileTotalSize = WavFileHeader.nRiffLength + 8;
    WavFileHeader.fileHeaderSize = WavFileHeader.fileTotalSize - WavFileHeader.fileDataSize;


    qDebug()<<"byte_per_sample"<<WavFileHeader.nBytesPerSample;
    qDebug()<<"wav_filedatasize"<<WavFileHeader.fileDataSize;
    qDebug()<<"sample_rate"<<WavFileHeader.nSampleRate;
    qDebug()<<"per bit in sample"<<WavFileHeader.nBitsPerSample;
    fileInfo.close();


//    QVector<double> waveData;
//     uint len = WavFileHeader.fileDataSize/WavFileHeader.nBytesPerSample;
//     qDebug()<<"len"<<len;
//     qDebug()<<__FUNCTION__<<pcmData.size()<<len;
//     if(WavFileHeader.nBytesPerSample == 1)//8位
//     {
//         char *data = (char *)pcmData.data();
//         for (uint i = 0; i < len; i++)
//         {
//             waveData.append(data[i]);
//         }
//     }
//     else//16位
//     {
//         short *data = (short *)pcmData.data();
//         for (uint i = 0; i < len; i++)
//         {
//             waveData.append(data[i]);
//         }
//     }
//     ui->widget_3->addGraph();
//     ui->widget_3->graph(0)->setPen(QPen(Qt::blue));

//     ui->widget_3->addGraph();
//     ui->widget_3->graph(1)->setPen(QPen(Qt::red));

//     QVector<double> x(len);
//     for (uint i=0; i<len; ++i)
//     {
//         x[i] = i;
//     }
//     QVector<double> lineX(2),lineY(2);
//     lineX[0]=lineX[1]=0;
//     lineY[0]=-100000;
//     lineY[1]=100000;
//     ui->widget_3->graph(0)->setData(x, waveData);
////     ui->widget_3->graph(1)->setData(lineX,lineY);
//     ui->widget_3->graph(0)->rescaleAxes();


    FILE *fp = NULL;

    Wav wav;
    RIFF_t riff;
    FMT_t fmt;
    Data_t data;

    fp = fopen("D:\\qtproject\\Video_Player\\video_test\\123.wav", "rb");
    if (!fp) {
        qDebug()<<("can't open audio file\n");
        return;
    }

    fread(&wav, 1, sizeof(wav), fp);

    riff = wav.riff;
    fmt = wav.fmt;
    data = wav.data;

    /**
     *  RIFF
     */
//    qDebug()<<("ChunkID \t\t%c%c%c%c\n", riff.ChunkID[0], riff.ChunkID[1], riff.ChunkID[2], riff.ChunkID[3]);
//    qDebug()<<("ChunkSize \t\t%d\n", riff.ChunkSize);
//    qDebug()<<("Format \t\t\t%c%c%c%c\n", riff.Format[0], riff.Format[1], riff.Format[2], riff.Format[3]);

//    qDebug()<<("\n");

    /**
     *  fmt
     */
//    qDebug()<<("Subchunk1ID \t%c%c%c%c\n", fmt.Subchunk1ID[0], fmt.Subchunk1ID[1], fmt.Subchunk1ID[2], fmt.Subchunk1ID[3]);
//    qDebug()<<("Subchunk1Size \t%d\n", fmt.Subchunk1Size);
//    qDebug()<<("AudioFormat \t%d\n", fmt.AudioFormat);
//    qDebug()<<("NumChannels \t%d\n", fmt.NumChannels);
//    qDebug()<<("SampleRate \t\t%d\n", fmt.SampleRate);
//    qDebug()<<("ByteRate \t\t%d\n", fmt.ByteRate);
//    qDebug()<<("BlockAlign \t\t%d\n", fmt.BlockAlign);
//    qDebug()<<("BitsPerSample \t%d\n", fmt.BitsPerSample);
    qDebug()<<"samplerate"<<fmt.SampleRate;
    qDebug()<<"duration"<<data.Subchunk2Size / fmt.ByteRate;

    qDebug()<<("\n");

    /**
     *  data
     */
//    qDebug()<<("blockID \t\t%c%c%c%c\n", data.Subchunk2ID[0], data.Subchunk2ID[1], data.Subchunk2ID[2], data.Subchunk2ID[3]);
//    qDebug()<<("blockSize \t\t%d\n", data.Subchunk2Size);

    qDebug()<<("\n");

//    duration = Subchunk2Size / ByteRate
    qDebug()<<("duration \t\t%d\n", data.Subchunk2Size / fmt.ByteRate);




}

void MainWindow::testWav(){
    WaveFile m_Wavefile;
    m_Wavefile.readWave("D:\\qtproject\\Video_Player\\video_test\\123.wav");
    qDebug()<<"vyte"<<m_Wavefile.getSampleNum();

}

void MainWindow::doBeforeChangeMedia(QString nextFilename){
//    if(this->current_index == -1);
//    else{
//        this->mediaplayer->stop();
//    }

//    audio_time = 0;
//    video_time = 0;
    qDebug()<<"ori的类型"<<ori_judgetype(nextFilename);
//    audio_wave.stop();

    dontshow = false;
    dontpreview = false;
    zero_tolerence = 0;
    ori_pos = -1;
//    ui->widget_4->setVisible(false);

    previewFrame.m_run = 2;

    if(ui->label_4->isVisible()){
        ui->label_4->setVisible(false);
    }


    if(previewFrame.before_start(nextFilename) == -1){
        dontpreview = true;
    }
    else{
        previewFrame.filename = nextFilename;
    }

    if(judgetype(nextFilename) == AUDIO_TYPE){

        this->type = AUDIO;
        ui->widget_2->type = 0;
        ui->label_4->raise();
        qDebug()<<"是audio";
//        audio_wave.stop();
        if(ui->widget->isVisible() == true)
            ui->widget->setVisible(false);
        if(ui->widget_3->isVisible() == false)
            ui->widget_3->setVisible(true);
        int r = audio_wave.init(nextFilename);
        if(r==-1){
            ui->widget_3->removeGraph(0);
            ui->widget_3->setVisible(false);
            dontshow = true;
            return;
        }
        old_position = 0;
        qDebug()<<"init完成";
        qDebug()<<"old_pos"<<old_position;
        ui->widget_3->removeGraph(0);
        QSharedPointer<QCPGraphDataContainer> dataContainer = ui->widget_3->addGraph()->data();
        ui->widget_3->graph(0)->setPen(QPen(Qt::blue));
        qDebug()<<"test point"<<old_position;
        QVector<QCPGraphData> plotData(m_bufferSize);
        for (size_t j = 0; j < m_bufferSize; j++)
        {
            plotData[j].key = j;
            plotData[j].value = 0;
        }
        dataContainer->set(plotData, true);
        ui->widget_3->xAxis->setRange(0, m_bufferSize);
    //    ui->widget_3->yAxis->setRange(0,10000);
        m_dataQueue.clear();
        m_drawBuffer = ui->widget_3->graph(0)->data().data();
        ui->widget_3->yAxis->setVisible(false);
        ui->widget_3->xAxis->setVisible(false);
    //    ui->widget_3->yAxis->setVisible(true);

    }
    else{
        if(judgetype(nextFilename) == VIDEO_TYPE){

            this->type = VIDEO;
            if(ori_judgetype(nextFilename) == AUDIO_TYPE){
                if(ui->widget->isVisible())
                    ui->widget->setVisible(false);
                ui->widget_2->type = 0;
                emit callVideoStop();
            }
            else{
                ui->widget_2->type = 1;

            }
            qDebug()<<"是video";
            if(ui->widget->isVisible()==false)
                ui->widget->setVisible(true);
            if(ui->widget_3->isVisible() == true)
                ui->widget_3->setVisible(false);
            m_dataQueue.clear();
        }
    }
    qDebug()<<"Dobefore结束";

}


void MainWindow::on_toolButton_10_clicked()
{
//    QDesktopWidget* desktopWidget = QApplication::desktop();
//    QRect deskRect = desktopWidget->availableGeometry();
//    double availableScreenX = deskRect.width();
//    double availableScreenY = deskRect.height();

    if(ui->toolButton_10->text() == "全屏"){

//     ui->toolButton_10->raise();
    ui->centralWidget->setWindowFlags (Qt::Window);
    ui->centralWidget->showFullScreen();
    ui->widget->move(0,0);
    ui->widget->resize(ui->centralWidget->width(),ui->centralWidget->height());

    ui->widget_2->move(0,0);
    ui->widget_2->resize(ui->centralWidget->width(),ui->centralWidget->height());
    ui->widget_3->move(0,0);
    ui->widget_3->resize(ui->centralWidget->width(),ui->centralWidget->height());
    ui->listWidget->setVisible(false);
    ui->textBrowser->setVisible(false);
    ui->toolButton->move(ori_toolbutton_x,ui->widget->height()-ui->toolButton->height()-10);
    ui->toolButton->raise();
    ui->toolButton_5->move(ori_toolbutton_5_x,ui->widget->height()-ui->toolButton_5->height()-10);
    ui->toolButton_5->raise();
    ui->toolButton_6->move(ori_toolbutton_6_x,ui->widget->height()-ui->toolButton_6->height()-10);
    ui->toolButton_6->raise();
    ui->horizontalSlider->move(ori_horizontalSlider_x, ui->widget->height()-ui->horizontalSlider->height()-10);
    ui->horizontalSlider->resize(ori_horizontalSlider_width+100,ui->horizontalSlider->height());
    ui->horizontalSlider->raise();
    ui->toolButton_2->move(ori_toolbutton_2_x + 100,ui->widget->height() - ui->toolButton_2->height()-10);
    ui->toolButton_2->raise();
    ui->toolButton_3->move(ori_toolbutton_3_x + 100,ui->widget->height() - ui->toolButton_3->height()-10);
    ui->toolButton_3->raise();
    ui->toolButton_4->move(ori_toolbutton_4_x + 100,ui->widget->height() - ui->toolButton_4->height()-10);
    ui->toolButton_4->raise();
    ui->comboBox->move(ori_combox_x+100,ui->widget->height()-ui->comboBox->height()-10);
    ui->comboBox->raise();
    ui->toolButton_7->move(ori_toolbutton_7_x + 100,ui->widget->height() - ui->toolButton_7->height()-10);
    ui->toolButton_7->raise();
    ui->toolButton_8->move(ori_toolbutton_8_x + 100,ui->widget->height() - ui->toolButton_8->height()-10);
    ui->toolButton_8->raise();
    ui->toolButton_10->move(ori_toolbutton_10_x + 100,ui->widget->height() - ui->toolButton_10->height()-10);
    ui->toolButton_10->raise();
    ui->label->move(ori_label_x + 100,ui->horizontalSlider->y() - ui->label->height() - 1);
    ui->label->raise();
    ui->label_2->move(ori_label_2_x + 100,ui->horizontalSlider->y() - ui->label_2->height() - 1);
    ui->label_2->raise();
    ui->label_3->move(ori_label_3_x + 100,ui->horizontalSlider->y() - ui->label_3->height() - 1);
    ui->label_3->raise();
    ui->label_4->move(ori_label_4_x,ui->horizontalSlider->y() - ui->label_4->height() - 1);
//    ui
    ui->label_4->setVisible(false);
    ui->label_4->raise();
    ui->verticalSlider->move(QApplication::desktop()->availableGeometry().width()-ori_verticalSlider_width-0.5,ui->widget->height() - ui->verticalSlider->height() - ui->toolButton_8->height()-10);
    ui->verticalSlider->raise();
    ui->toolButton_9->move(ori_toolbutton_9_x,ui->widget_2->height() - ui->toolButton_9->height() - 10);
    ui->toolButton_9->raise();
    ui->horizontalSlider_2->move(ori_horizontalSlider_2_x, ui->widget_2->y()+ui->widget_2->height()-ui->horizontalSlider_2->height()-10);
    ui->horizontalSlider_2->resize(ori_horizontalSlider_2_width+100,ui->horizontalSlider_2->height());
    ui->horizontalSlider_2->raise();
    ui->toolButton_10->setText("取消全屏");
    ui->label_5->move(ori_label_5_x + 100,ui->horizontalSlider->y() - ui->label_5->height() - 1);
    ui->label_5->raise();
    ui->label_6->move(ori_label_6_x + 100,ui->horizontalSlider->y() - ui->label_6->height() - 1);
    ui->label_6->raise();
    ui->label_7->move(ori_label_7_x + 100,ui->horizontalSlider->y() - ui->label_7->height() - 1);
    ui->label_7->raise();

    this->isFullScreen = true;

    m_pTimer_fullscreen->stop();
    m_pTimer_fullscreen->start(5000);


    return;
    }
    if(ui->toolButton_10->text() == "取消全屏"){
        this->isFullScreen = false;
        m_pTimer_fullscreen->stop();
//        m_pTimer_fullscreen->stop();
        ui->centralWidget->setWindowFlags (Qt::SubWindow);
        ui->centralWidget->showNormal();
        ui->widget->move(ori_widget_x,ori_widget_y);
        ui->widget->resize(ori_widget_width,ori_widget_height);
        ui->widget_2->move(ori_widget_2_x,ori_widget_2_y);
        ui->widget_2->resize(ori_widget_2_width,ori_widget_2_height);
        ui->widget_3->move(ori_widget_3_x,ori_widget_3_y);
        ui->widget_3->resize(ori_widget_3_width,ori_widget_3_height);
        ui->horizontalSlider->move(ori_horizontalSlider_x,ori_horizontalSlider_y);
        ui->horizontalSlider->resize(ori_horizontalSlider_width,ori_horizontalSlider_height);
        ui->toolButton->move(ori_toolbutton_x,ori_toolbutton_y);
        ui->toolButton->resize(ori_toolbutton_width,ori_toolbutton_height);
        ui->toolButton_2->move(ori_toolbutton_2_x,ori_toolbutton_2_y);
        ui->toolButton_2->resize(ori_toolbutton_2_width,ori_toolbutton_2_height);
        ui->toolButton_3->move(ori_toolbutton_3_x,ori_toolbutton_3_y);
        ui->toolButton_3->resize(ori_toolbutton_3_width,ori_toolbutton_3_height);
        ui->toolButton_4->move(ori_toolbutton_4_x,ori_toolbutton_4_y);
        ui->toolButton_4->resize(ori_toolbutton_4_width,ori_toolbutton_4_height);
        ui->comboBox->move(ori_combox_x,ori_combox_y);
        ui->comboBox->resize(ori_combox_width,ori_combox_height);
        ui->label->move(ori_label_x,ori_label_y);
        ui->label->resize(ori_label_width,ori_label_height);
        ui->label_2->move(ori_label_2_x,ori_label_2_y);
        ui->label_2->resize(ori_label_2_width,ori_label_2_height);
        ui->label_3->move(ori_label_3_x,ori_label_3_y);
        ui->label_3->resize(ori_label_3_width,ori_label_3_height);
//        ui->label_4->move(ori_label_4_x,ori_label_4_y);
        ui->label_4->setVisible(false);
        ui->toolButton_5->move(ori_toolbutton_5_x,ori_toolbutton_5_y);

        ui->toolButton_5->resize(ori_toolbutton_5_width,ori_toolbutton_5_height);
        ui->toolButton_6->move(ori_toolbutton_6_x,ori_toolbutton_6_y);
        ui->toolButton_6->resize(ori_toolbutton_6_width,ori_toolbutton_6_height);
        ui->toolButton_7->move(ori_toolbutton_7_x,ori_toolbutton_7_y);
        ui->toolButton_7->resize(ori_toolbutton_7_width,ori_toolbutton_7_height);
        ui->toolButton_8->move(ori_toolbutton_8_x,ori_toolbutton_8_y);
        ui->toolButton_8->resize(ori_toolbutton_8_width,ori_toolbutton_8_height);
        ui->toolButton_10->move(ori_toolbutton_10_x,ori_toolbutton_10_y);
        ui->toolButton_10->resize(ori_toolbutton_10_width,ori_toolbutton_10_height);
        ui->toolButton_10->setText("全屏");
        ui->verticalSlider->move(ori_verticalSlider_x,ori_verticalSlider_y);
        ui->verticalSlider->resize(ori_verticalSlider_width,ori_verticalSlider_height);

        ui->toolButton_9->move(ori_toolbutton_9_x,ori_toolbutton_9_y);
        ui->toolButton_9->resize(ori_toolbutton_9_width,ori_toolbutton_9_height);
        ui->horizontalSlider_2->move(ori_horizontalSlider_2_x,ori_horizontalSlider_2_y);
        ui->horizontalSlider_2->resize(ori_horizontalSlider_2_width,ori_horizontalSlider_2_height);
        ui->label_5->move(ori_label_5_x,ori_label_5_y);
        ui->label_5->resize(ori_label_5_width,ori_label_5_height);
        ui->label_6->move(ori_label_6_x,ori_label_6_y);
        ui->label_6->resize(ori_label_6_width,ori_label_6_height);
        ui->label_7->move(ori_label_7_x,ori_label_7_y);
        ui->label_7->resize(ori_label_7_width,ori_label_7_height);

        ui->listWidget->setVisible(true);
        ui->textBrowser->setVisible(true);

    }

//    qDebug()<<"4'x"<<ui->label_4->x();
//    qDebug()<<"4'y"<<ui->label_4->y();



//    ui->centralWidget->resize(900,900);
//    ui->widget->resize(
//                QApplication::desktop()->width(),
//                QApplication::desktop()->height());

//    ui->toolButton->raise();

//    ui->toolButton->show();

//    ui->listWidget->raise();

//    ui->listWidget->move(200,200);

//    ui->listWidget->show();

}

//void MainWindow::restartPreviewFrame(){
////    previewFrame.m_run = 1;
//    qDebug()<<"失败归来";
//    continue_ = true;
////    previewFrame.start();
//}

void MainWindow::on_timer_timeout(){
//    qDebug()<<"是加你断了qqqqq";
    ui->label_4->setPixmap(QPixmap());
//    qDebug()<<"mouse_x"<<mouse_x;
//    qDebug()<<"mouse_y"<<mouse_y;
//    qint64 position = preframe_mouse_x*ui->horizontalSlider->maximum()/ui->horizontalSlider->width();
//    qDebug()<<"pos"<<transfer_to_std_time(position);
    if(dontpreview == false){
    qint64 position = preframe_mouse_x*ui->horizontalSlider->maximum()/ui->horizontalSlider->width();
    qDebug()<<"pos"<<transfer_to_std_time(position);
//    qDebug()<<"又来了";
    this->pause_time = position;
    ui->label_4->move(preframe_mouse_x+ui->horizontalSlider->x(),ui->horizontalSlider->y()-ui->label_4->height());
//    ui->label_4->setPixmap(QPixmap("D:\\images\\72.jpg"));
    previewFrame.time = position / 1000;
//        previewFrame.time = 60;
//    previewFrame.filename = this->playList[this->current_index];
//            while(continue_ == false && previewFrame.m_run !=0){
//                qDebug()<<"出不去";
//            }

    previewFrame.start();
    ui->label_4->setScaledContents(true);
    }

}

void MainWindow::on_timer_timeout_fullscreen(){
//    qDebug()<<"隐藏了哦";
    if(this->isFullScreen == true){
    ui->centralWidget->setCursor(Qt::BlankCursor); //隐藏鼠标
    if(!this->isReverse){
        ui->toolButton->setVisible(false);
        ui->horizontalSlider->setVisible(false);
        ui->label->setVisible(false);
        ui->label_2->setVisible(false);
        ui->label_3->setVisible(false);
        ui->toolButton_5->setVisible(false);
        ui->toolButton_6->setVisible(false);
        ui->label_4->setVisible(false);
    }
    if(this->isReverse){
        ui->toolButton_9->setVisible(false);
        ui->horizontalSlider_2->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);
        ui->label_7->setVisible(false);
    }

//    ui->toolButton_10->setVisible(false);

    ui->toolButton_2->setVisible(false);
    ui->toolButton_3->setVisible(false);
    ui->toolButton_4->setVisible(false);
    ui->toolButton_7->setVisible(false);
    ui->toolButton_8->setVisible(false);
    ui->toolButton_10->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->verticalSlider->setVisible(false);


    }
    else{
        ui->centralWidget->setCursor(Qt::ArrowCursor);
        if(!this->isReverse){
            ui->toolButton->setVisible(true);
            ui->horizontalSlider->setVisible(true);
            ui->label->setVisible(true);
            ui->label_2->setVisible(true);
            ui->label_3->setVisible(true);
            ui->toolButton_5->setVisible(true);
            ui->toolButton_6->setVisible(true);
//            ui->label_4->setVisible(true);

        }
        if(this->isReverse){
            ui->toolButton_9->setVisible(true);
            ui->horizontalSlider_2->setVisible(true);
            ui->label_5->setVisible(true);
            ui->label_6->setVisible(true);
            ui->label_7->setVisible(true);
        }

        ui->toolButton_2->setVisible(true);
        ui->toolButton_3->setVisible(true);
        ui->toolButton_4->setVisible(true);
        ui->toolButton_7->setVisible(true);
        ui->toolButton_8->setVisible(true);
        ui->toolButton_10->setVisible(true);
        ui->comboBox->setVisible(true);
        ui->verticalSlider->setVisible(true);

    }
//    m_pTimer->stop();
}

void MainWindow::sleepforms(){

//    qDebug()<<"金老";
//    QTime dieTime = QTime::currentTime().addMSecs(40);
//    qDebug()<<"die"<<dieTime;
//    while( QTime::currentTime() < dieTime ){
//        qDebug()<<"还在里面";
//        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//    }
//    QEventLoop loop;//定义一个新的事件循环
//    QTimer::singleShot(40, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
//    loop.exec();
//        qDebug()<<"金老chu'lai";

}

void MainWindow::threadFinished2(){
    if((
        DecodeWork2.finished == true && DecodeWorkAudio2.finished == true)){
        recoverFromCacheFile();
        this->m_pTimer_2->stop();
        return;
    }


}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ;
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    ;
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ;
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    ;
}


void MainWindow::no_video_handle(){
    ui->widget_2->type = 0;
}


void MainWindow::videosleep(qint64 time){
    qDebug()<<"video休眠"<<time;
    DecodeWork.sleeptime = time;
}

void MainWindow::audiosleep(qint64 time){
//    if(type == AUDIO && ui->widget_2->type == 0){
//        return;
//    }
//    else{

//        qDebug()<<"audio休眠"<<time;
//        DecodeWorkAudio.sleeptime = time;
//    }
}


void MainWindow::set_audio_s_video_time(qint64 video_time)
{
//    qDebug()<<"设置video_time,norem"<<video_time;
    DecodeWorkAudio.setVideoTime(video_time);
}

void MainWindow::resizeEvent( QResizeEvent* e)
{
         QSize oldSize,size;
         oldSize = e->oldSize(); //获取开始的size
         size = e->size();       //获取现在的size

         //获取长宽变化的比率
         qreal ratioW,ratioH;
         ratioW = size.width()/oldSize.width();
         ratioH = size.height()/oldSize.height();

         //窗体中的控件按比例缩放
//         ui->toolButton->resize(QSize(ui->toolButton->size().width()*ratioW,

//                                     ui->toolButton->size().height()*ratioH));
//         ui->toolButton->raise();
//         //如果你有很多控件，请继续缩放下去……
//         ..............
}


void MainWindow::setCallBack(){
    qDebug()<<"怎么办呀";
    previewFrame.callback1 = true;
    m_pTimer_preframe->stop();
}

void MainWindow::start_timer(){
//    qDebug()<<"开始设置";
//    m_pTimer_preframe->stop();
//    m_pTimer_preframe->start(100);
}

void MainWindow::stoptimer(){
//    m_pTimer_preframe->stop();
}

void MainWindow::playCacheFile(){
    this->mediaplayer->setMedia(QUrl::fromLocalFile(""));
    this->play();
    m_pTimer_2->start(4500);
    qDebug()<<"播放新东西";
    this->isCacheFile = true;
//    qDebug()<<"s"<<s;
    ui->toolButton->setEnabled(false);
    ui->horizontalSlider->setEnabled(false);
    ui->horizontalSlider->setMouseTracking(false);
    ui->label->setEnabled(false);
    ui->label_2->setEnabled(false);
    ui->label_3->setEnabled(false);
//    ui->label_4->setEnabled(false);
    ui->toolButton_2->setEnabled(false);
    ui->toolButton_3->setEnabled(false);
    ui->toolButton_4->setEnabled(false);
    ui->toolButton_5->setEnabled(false);
    ui->toolButton_6->setEnabled(false);
    ui->toolButton_7->setEnabled(false);
    ui->toolButton_8->setEnabled(false);
    ui->toolButton_10->setEnabled(false);
    ui->verticalSlider->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->listWidget->setEnabled(false);
    DecodeWork2.SetSate(0);
    DecodeWorkAudio2.SetSate(0);
    DecodeWork2.LoadVideoFile(playList[current_index]);
    DecodeWorkAudio2.LoadVideoFile(playList[current_index]);
//            qDebug()<<"凯斯到了";
    DecodeWork2.SetSate(1);
    DecodeWorkAudio2.SetSate(1);

    DecodeWork2.video_pack.clear();
    DecodeWork2.over_pack.clear();

    DecodeWorkAudio2.audio_pack.clear();
    DecodeWorkAudio2.over_pack.clear();

    qint64 duration = DecodeWork2.GetDuration();
    DecodeWork2.SetSeekPos(duration);
    DecodeWork2.start();
    DecodeWorkAudio2.setVideoTime(duration);
    DecodeWorkAudio2.SetSeekPos(duration);
    DecodeWorkAudio2.start();



//    mediaplayer->stop();
//    mediaplayer->setMedia(QUrl::fromLocalFile(QDir::currentPath()+"/blank.mp3"));
//    qDebug()<<"cache file duration"<<mediaplayer->duration();
//    mediaplayer->play();
//    qDebug()<<"duration of cache"<<mediaplayer->duration();




}

void MainWindow::recoverFromCacheFile(){
//    this->isCacheFile = true;
    ui->toolButton->setEnabled(true);
    ui->horizontalSlider->setEnabled(true);
    ui->horizontalSlider->setMouseTracking(true);
    ui->label->setEnabled(true);
    ui->label_2->setEnabled(true);
    ui->label_3->setEnabled(true);
    ui->toolButton_2->setEnabled(true);
    ui->toolButton_3->setEnabled(true);
    ui->toolButton_4->setEnabled(true);
    ui->toolButton_5->setEnabled(true);
    ui->toolButton_6->setEnabled(true);
    ui->toolButton_7->setEnabled(true);
    ui->toolButton_8->setEnabled(true);
    ui->toolButton_10->setEnabled(true);
    ui->verticalSlider->setEnabled(true);
    ui->comboBox->setEnabled(true);
    ui->listWidget->setEnabled(true);

    this->mediaplayer->setMedia(QUrl::fromLocalFile(playList[current_index]));
//    this->mediaplayer->setPosition(200);
    this->mediaplayer->play();
    this->isCacheFile = false;
    this->notkey = false;
    zero_tolerence = 0;


}


void MainWindow::mediaStateChanged2(QMediaPlayer::State state){
//    qDebug()<<"state"<<state;
//    switch (state) {
//    case QMediaPlayer::PlayingState://Playing状态
//        ui->toolButton->setToolTip("暂停");
//        ui->toolButton->setIcon(QPixmap(":/images/pause.png"));
//        break;
//    default://Pause或者Stop状态
//        ui->toolButton->setToolTip("播放");
//        ui->toolButton->setIcon(QPixmap(":/images/play.png"));
//        break;
//    }
}

void MainWindow::on_time_timeout_2(){
    DecodeWork2.StopPlay();
    DecodeWorkAudio2.StopPlay();
}

