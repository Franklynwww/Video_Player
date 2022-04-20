#-------------------------------------------------
#
# Project created by QtCreator 2022-03-31T17:43:34
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += multimediawidgets
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Video_Player
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    ReverseDecode.cpp \
    ReverseDecode_AuDio.cpp \
    VideoFrameDisplay.cpp \
    VideoJPG.cpp \
    VideoSurface.cpp \
        main.cpp \
        mainwindow.cpp \
    utils.cpp \
    openfilethread.cpp

HEADERS += \
    ReverseDecode.h \
    ReverseDecode_Audio.h \
    VideoFrameDisplay.h \
    VideoJPG.h \
    VideoSurface.h \
        mainwindow.h \
    utils.h \
    openfilethread.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    video_player.qrc

CONFIG += exceptions



win32: {
    FFMPEG_HOME=$$PWD/ffmpeg
    #设置 ffmpeg 的头文件
    INCLUDEPATH += $$FFMPEG_HOME/include

    #设置导入库的目录一边程序可以找到导入库
    # -L ：指定导入库的目录
    # -l ：指定要导入的 库名称
    LIBS +=  -L$$FFMPEG_HOME/lib \
             -lavcodec \
             -lavdevice \
             -lavfilter \
            -lavformat \
            -lavutil \
            -lpostproc \
            -lswresample \
            -lswscale
}


