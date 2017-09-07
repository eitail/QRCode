#****************************************************************************
#
# @brief 二维码生成器
# @author Michael Li
# @date 2016.6.30 12:31
# @URL http://www.linuxkiss.com
#
#****************************************************************************

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRpic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qrencode/bitstream.c \
    qrencode/mask.c \
    qrencode/mmask.c \
    qrencode/mqrspec.c \
    qrencode/qrencode.c \
    qrencode/qrinput.c \
    qrencode/qrspec.c \
    qrencode/rscode.c \
    qrencode/split.c \
    writeQRCode.cpp \
    QRCodeUrl.cpp

HEADERS  += mainwindow.h \
    qrencode/bitstream.h \
    qrencode/config.h \
    qrencode/mask.h \
    qrencode/mmask.h \
    qrencode/mqrspec.h \
    qrencode/qrencode.h \
    qrencode/qrencode_inner.h \
    qrencode/qrinput.h \
    qrencode/qrspec.h \
    qrencode/rscode.h \
    qrencode/split.h \
    writeQRCode.h \
    QRCodeUrl.h

FORMS    += mainwindow.ui

RESOURCES += \
    q.qrc
