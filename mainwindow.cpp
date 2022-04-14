#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"utils.h"
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

    this->grabKeyboard();
    ui->setupUi(this);
    //设置主界面背景
    QPixmap pixmap(":/images/all.jpg");
    QPalette palette;
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
//    ui->centralWidget->setStyleSheet("background-image:url(:/images/play.png);background-repeat:no-repeat;");
    //创建mediaplayer
    //先禁止最大化
    setWindowFlags(windowFlags() &~ Qt::WindowMaximizeButtonHint);
    mediaplayer = new QMediaPlayer(this);
    //设置对应mediaplayer的QVideoWidget
    mediaplayer->setVideoOutput(ui->widget);
    //设置播放按钮
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


//    ui->listWidget->setStyleSheet(
//    "QListWidget::item{background-color:rgba(255,255,255,1);border-width:2px;border-radius:4px;margin:4px 0px 0px 0px;}"
//    "QListWidget::item:hover{background-color:rgba(223,223,223,0.9);}"
//    "QListWidget::item::selected:active{background-color:rgba(220,220,220,1);color:black;}"
//    );

    //设置播放属性
    //1、监听信号变化函数,signal为内置的信号函数stateChanged，slot为自己定义的槽函数mediaStateChanged
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
    ui->horizontalSlider->installEventFilter(this);
    ui->horizontalSlider->setMouseTracking(true);
    // 9. 刷新列表
    connect(this,SIGNAL(playListChanged(void)),this,SLOT(reloadListWidget()));

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



      initPlayList();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::play(){
    switch (this->mediaplayer->state()) {
    case QMediaPlayer::PlayingState: //Playing状态
        this->mediaplayer->pause();
        break;
    default:  // Pause或者Stop状态
//        VideoSurface * v = new VideoSurface();
//        this->mediaplayer->setVideoOutput(v);
//        this->mediaplayer->setMuted(true);
//        connect(v, SIGNAL(frameAvailable(QVideoFrame &)), this, SLOT(ProcessFrame(QVideoFrame &)));
        this->mediaplayer->play();
        break;
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
    //
//    qDebug()<<position;
    ui->label_2->setText(transfer_to_std_time(position));
    ui->horizontalSlider->setValue(position);
}

void MainWindow::setPosition(int position){
    //
    mediaplayer->setPosition(position);
    
}

void MainWindow::durationChanged(qint64 duration){ //槽函数，触发条件：视频时长改变
    //
//    qDebug()<<duration;
    ui->label->setText(transfer_to_std_time(duration));
    ui->horizontalSlider->setRange(0,duration); 
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
                                           tr("打开的文件不是音频格式")
                                           );
            return;
        }
        mediaplayer->setMedia(QUrl::fromLocalFile(filename));

        ui->toolButton->setAutoRaise(true);
        this->mediaplayer->play();
    }
    QT_CATCH(QMediaPlayer::Error e){
        qDebug()<<"出错了";
        return;
    }

    ui->toolButton->setEnabled(true);
    this->addInPlayList(filename);


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

bool MainWindow::findInPlayList(QString filename){
    return this->playList.indexOf(filename) != -1;
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

    if (this->findInPlayList(filename)){
        this->playList.removeOne(filename);
        this->playList.insert(0,filename);
        this->current_index = 0;
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

    }


    qDebug()<<"最后的list"<<playList;

    //TODO: 在退出窗口之前，实现希望做的操作
    rewriteFile();

}


void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    this->current_index = index.row();
    QString item_text = ui->listWidget->item(this->current_index)->text();
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
        qDebug()<<"文件存在";
        this->mediaplayer->setMedia(QUrl::fromLocalFile(filename));
        this->play();
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
       QMessageBox::warning(this, tr("Error"),
                                      tr("打开的文件已不存在")
                                      );
       this->playList.removeOne(filename);

       emit playListChanged();

    }

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
//    QAction *clearSeeds = new QAction(tr("Clear"), this);
    popMenu->addAction( deleteItem );
//    popMenu->addAction( clearSeeds );
    connect( deleteItem, SIGNAL(triggered() ), this, SLOT( deleteItemSlot()) );
//    connect( clearSeeds, SIGNAL(triggered() ), this, SLOT( clearSeedsSlot()) );
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
    this->playList.removeAt(curIndex);
    emit playListChanged();
//    if (this->playList.length() == 0){
//        this->mediaplayer->setMedia(NULL);
//        this->current_index = -1;
//        this->play();
//        return;
//    }
    if(this->current_index==curIndex){
        getNextAccessible(curIndex);
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

void MainWindow::getNextAccessible(int first_index){
    qDebug()<<"first_index"<<first_index;
    int cur_index = first_index;
    while (cur_index<this->playList.length()){
        QString nextfilename = this->playList[cur_index];
        QFile file(nextfilename);
        if (file.exists()){
            this->current_index = cur_index;
            this->mediaplayer->setMedia(QUrl::fromLocalFile(nextfilename));
            this->play();
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
    cur_index = 0;
    while (this->playList.length()>0){
        QString nextfilename = this->playList[cur_index];
        QFile file(nextfilename);
        if (file.exists()){
            this->current_index = cur_index;
            this->mediaplayer->setMedia(QUrl::fromLocalFile(nextfilename));
            this->play();
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
        emit playListChanged();
        return;
    }




}

void MainWindow::getPreviousAccessible(int first_index){
    int cur_index = first_index;
    while (cur_index>=0 && this->playList.length()>0){
        QString prefilename = this->playList[cur_index];
        QFile file(prefilename);
        if (file.exists()){
            this->current_index = cur_index;
            this->mediaplayer->setMedia(QUrl::fromLocalFile(prefilename));
            this->play();
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
    cur_index = this->playList.length() - 1;
    while (this->playList.length()>0){
        QString prefilename = this->playList[cur_index];
        QFile file(prefilename);
        if (file.exists()){
            this->current_index = cur_index;
            this->mediaplayer->setMedia(QUrl::fromLocalFile(prefilename));
            this->play();
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
        emit playListChanged();
        return;
    }

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


void MainWindow::ProcessFrame(QVideoFrame &frame)
{
    static int count = 0;
    qDebug() << "=============ProcessFrame===============";
    qDebug() << "width : " << frame.width() << " height : " << frame.height();
    qDebug() << "start time : " << frame.startTime()/1000 << "ms";
    qDebug() << "end time : " << frame.endTime()/1000 << "ms";
    qDebug() << "pixelFormat :" << frame.pixelFormat();

    frame.map(QAbstractVideoBuffer::ReadOnly);
    QImage recvImage(frame.bits(), frame.width(), frame.height(), QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));
    recvImage.save(QString("D:/images/%1.jpg").arg(count++), "JPG");
    qDebug() << "frame data size :" << frame.mappedBytes();
//    update();
    frame.unmap();
}

//实现mouseMoveEvent
void MainWindow::mouseMoveEvent(QMouseEvent *event){
//    qDebug()<<"ok";
//    // 判断鼠标是否在pushButton上
//    if (ui->horizontalSlider->geometry().contains(this->mapFromGlobal(QCursor::pos())))
//    {
//        // do something...
//        qDebug()<<111;
//    }
//    emit mouseMoved(event);
}




//使用eventFilter实现mousePressEvent
bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui->horizontalSlider)
    {
        if (e->type() == QEvent::MouseButtonPress){
           int mouse_x = static_cast<QMouseEvent *>(e)->x();
//           qDebug()<<mouse_x;
//           qDebug()<<ui->horizontalSlider->width();
//           qDebug()<<ui->horizontalSlider->maximum();
           qint64 position = mouse_x*ui->horizontalSlider->maximum()/ui->horizontalSlider->width();
//           qDebug()<<position;
//           ui->horizontalSlider->setValue(position);
           this->mediaplayer->setPosition(position);
//            emit mousePress(e);
//           QPixmap pixmap(":/images/all.jpg");
//           QPalette palette;
//           palette.setBrush(backgroundRole(),QBrush(pixmap));
//           ui->horizontalSlider->setPalette(palette);
        }
    }
    return QWidget::eventFilter(obj,e);
}

void MainWindow::presentframe(const QVideoFrame & frame){
    qDebug()<<"present frame";
    QVideoFrame frametodraw(frame);
    if(!frametodraw.map(QAbstractVideoBuffer::ReadOnly))
        return;
    QImage img = QImage(frame.bits(),
                frame.width(),
                frame.height(),
                frame.bytesPerLine(),
                QVideoFrame::imageFormatFromPixelFormat(frametodraw.pixelFormat())
                //QImage::Format_RGB32
                );
    img = img.mirrored(false, true);//图像垂直翻转(图像是倒置的，调用该函数可正置。同时该函数也解决了频繁的内存错误引起的崩溃, 原因不明)
    qDebug()<<img.size();
    //这里可以分析或编辑图像后再输出显示视频
    //视频的显示则利用重写paintEvent()函数来绘制实现。还可以直接将图像设置到label控件中，也会形成视频。
    update();                       //通知Qt重绘

    frametodraw.unmap();


}

void MainWindow::back(){
    qint64 old_position = this->mediaplayer->position();
    qint64 new_position = old_position - 1000;
    if (new_position < 0){
        return;
    }
    this->mediaplayer->setPosition(new_position);
}

void MainWindow::forward(){
    qint64 old_position = this->mediaplayer->position();
    qint64 new_position = old_position + 1000;
    if (new_position > this->mediaplayer->duration()){
        return;
    }
    this->mediaplayer->setPosition(new_position);
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    QString key_info = QKeySequence(e->modifiers() + e->key()).toString();
    qDebug()<<key_info;
    if (this->current_index == -1){
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
