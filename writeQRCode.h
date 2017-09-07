/****************************************************************************
**
** @brief 这个类是生成二维码的类
** @author Michael Li
** @date 2016.6.30 12:31
** @URL http://www.linuxkiss.com
**
****************************************************************************/
#ifndef WRITEQRCODE_H
#define WRITEQRCODE_H

#define PIC_SIZE_W_H       (95)

#include <QLabel>
#include <QDebug>
#include <QIcon>
#include <QWidget>
#include <QPainter>
#include <QSpacerItem>
#include <QByteArray>
#include <QPaintEvent>
#include <QDateTime>
#include <QDir>
#include "qrencode/qrencode.h"

#include "QRCodeUrl.h"

class writeQRCode : public QLabel
{
    Q_OBJECT
    enum QR_MODE {
        MODE_NUL = QR_MODE_NUL,
        MODE_NUM = QR_MODE_NUM,
        MODE_AN = QR_MODE_AN,
        MODE_8 = QR_MODE_8,
        MODE_KANJI = QR_MODE_KANJI,
        MODE_STRUCTURE = QR_MODE_STRUCTURE,
        MODE_ECI = QR_MODE_ECI,
        MODE_FNC1FIRST = QR_MODE_FNC1FIRST,
        MODE_FNC1SECOND = QR_MODE_FNC1SECOND
    };

    enum QR_LEVEL {
        LEVEL_L = QR_ECLEVEL_L,
        LEVEL_M = QR_ECLEVEL_M,
        LEVEL_Q = QR_ECLEVEL_Q,
        LEVEL_H = QR_ECLEVEL_H
    };


public:
    explicit  writeQRCode(QWidget *parent = 0);

protected:
    void paintEvent (QPaintEvent *event);

public:
    QLabel *        m_plabel;
    bool            is_save;
    QString         str;
    int             m_OkNum;
    int             m_AllNum;
    int             m_width;

    QMap<QRcode *,int>  m_cQrcode;

private:
    bool            casesen;
    int             margin;
    QIcon           icon;
    qreal           percent;
    QByteArray      text;
    QColor          foreground;
    QColor          background;
    QR_MODE         mode;
    QR_LEVEL        level;
    QRCodeUrl*          m_QRCodeUrl;

};

#endif // WRITEQRCODE_H
