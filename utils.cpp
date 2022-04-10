#include "utils.h"
bool isValidVideoFile(QString filename){
    filename = filename.toLower();
    int lastindex = filename.lastIndexOf(".");
    QString type = "";
    for (int i = lastindex+1;i<filename.length();i++){
        type += filename[i];
    }
    if (type == "avi" || type == "wmv" || type == "mpg" || type == "mpeg" || type == "mov" || type == "rm"
            || type == "ram" || type == "swf" || type == "flv" || type == "mp4" || type == "mp3" || type == "wma"
            || type == "rmvb" || type == "mkv"){
        return true;
    }
    return false;
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
