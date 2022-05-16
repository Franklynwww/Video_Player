#include "mainwindow.h"
#include"VideoJPG.h"
#include <QApplication>
#include <QTextCodec>
//#include <QProcess>
//#include <QDir>
//#include <QString>



//extern "C"
//{
//#include "libavcodec/avcodec.h"
//}

int main(int argc, char *argv[])
{

//    QString strInfo;
//    QProcess p(nullptr);
//    QProcess p2(nullptr);
//    QProcess p3(nullptr);
//    QString curPath = QDir::currentPath();//获取当前应用程序目录
//    QFile f("D:\\qt_txt.txt");
//    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
//    {
//        qDebug() << ("打开文件失败");
//    }
//    QTextStream txtOutput(&f);
//    QString str = curPath;
//    txtOutput << str << endl;
//    f.close();

//    qDebug()<<"current_path"<<curPath;
//    QString toolpath;
//    toolpath = "/LAV Filters/x64/";    // 当前运行路径下的文件夹（其中是需要调用的.bat
//    curPath.append(toolpath);  //利用append方法在路径字符串后添加文件夹字符串
//    p.setWorkingDirectory(curPath); //设置工作目录
//    toolpath = "/make.bat";  //要调用的脚本文件
//    curPath.append(toolpath); //添加脚本文件字符串
//    p.start(curPath);  //运行脚本文件
//    if(p.waitForFinished()){      //等待脚本运行完成，超时时间默认是3000s,超时返回0，正常返回1
//        qDebug()<<"完成配置！";
//    }else{
//        qDebug()<<"bat运行错误！";
//    }
//    qDebug() << p.errorString();


    qDebug()<<av_version_info();
//    qDebug()<<avcodec_configuration();
    QTextCodec *code = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(code);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}
