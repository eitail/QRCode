#include "QRCodeUrl.h"

QRCodeUrl::QRCodeUrl()
{
    m_Url           = "";
    m_Num           = 0;
    m_OkNum         = 0;
    m_QrCode_w_h    = 0;
    m_isStartPaint  = false;
    m_text_p        = "";
    m_text_c        = "";
    m_isOK          = false;
    m_Path          = "";
}

QRCodeUrl* QRCodeUrl::m_pInstance = NULL;
QRCodeUrl* QRCodeUrl::getInstance()
{
    if( m_pInstance == NULL)
    {
       m_pInstance =  new QRCodeUrl();

    }
    return m_pInstance;
}
