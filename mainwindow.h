#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QVideoWidget>
#include<QMediaPlayer>
#include<QCloseEvent>
#include"VideoSurface.h"


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
    Ui::MainWindow *ui;
    QMediaPlayer * mediaplayer;
    VideoSurface * videosurface;

    QString filepath; // 文件
    QStringList playList;//播放列表
    int current_index;
    int mouse_x;
    int mouse_y;

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



signals:
    void playListChanged();


private slots:
    //播放函数
    void play();
    //获取播放状态
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
    void on_horizontalSlider_sliderPressed();
    void on_horizontalSlider_actionTriggered(int action);
    void on_comboBox_currentIndexChanged(const QString &arg1);

    void updateInfo();

    void ProcessFrame(QVideoFrame &frame);

    void presentframe(const QVideoFrame & frame);

    void keyPressEvent(QKeyEvent *e);


    void on_toolButton_5_clicked();
    void on_toolButton_6_clicked();
};

#endif // MAINWINDOW_H
