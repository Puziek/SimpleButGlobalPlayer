#-------------------------------------------------
#
# Project created by QtCreator 2016-09-29T08:25:02
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MediaPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mediaplayer.cpp \
    playlistmodel.cpp \
    playercontrols.cpp \
    videowidget.cpp

HEADERS  += mediaplayer.h \
    playlistmodel.h \
    playercontrols.h \
    videowidget.h

FORMS    += mediaplayer.ui \
    playercontrols.ui
