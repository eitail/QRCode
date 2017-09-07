/****************************************************************************
**
** @brief 这个类是将mainwindow和writeQRCode之间变量相互赋值读取
** @author Michael Li
** @date 2016.6.30 12:31
** @URL http://www.linuxkiss.com
**
****************************************************************************/
#ifndef QRCODEURL_H
#define QRCODEURL_H

#include <QByteArray>
#include <QString>

class QRCodeUrl
{
    public:
        static      QRCodeUrl*      getInstance();
        QRCodeUrl();

    private:


    public:
        QString         m_Url;
        int             m_Num;
        int             m_OkNum;
        int             m_QrCode_w_h;
        bool            m_isStartPaint;
        QByteArray      m_text_p;
        QByteArray      m_text_c;
        bool            m_isOK;
        QString         m_Path;

    private:
        static      QRCodeUrl *         m_pInstance;

};

#endif // QRCODEURL_H
