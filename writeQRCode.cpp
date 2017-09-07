#include "writeQRCode.h"

writeQRCode::writeQRCode(QWidget *parent):QLabel(parent)
{
    m_QRCodeUrl = QRCodeUrl::getInstance();
}


/**
 * @brief 开始绘制二维码
 * @param event
 */
void writeQRCode::paintEvent (QPaintEvent *event)
{
    //原始text信息
    m_QRCodeUrl-> m_text_p    = (m_QRCodeUrl->m_Url+QString::number(m_QRCodeUrl->m_OkNum)).toLatin1();
    //Base64加密后的值（这个值跟随自己需求赋值）
    m_QRCodeUrl-> m_text_c    = (m_QRCodeUrl->m_Url+QString::number(m_QRCodeUrl->m_OkNum)).toLatin1().toBase64();
    //将需要生成二维码的信息赋值给text
    text                    = m_QRCodeUrl-> m_text_c;
    QString pinName         = text.data();
    m_width                 = m_QRCodeUrl->m_QrCode_w_h;
    //设置总共需要生成几张二维码
    m_AllNum                = m_QRCodeUrl->m_Num;

    /*
     * 判断
     * 这张二维码是否画完，false就开始画
     * 是否点击开始按钮
     * 是否画的二维码小于设定的张数，小于就画
     *
     */
    if( !m_QRCodeUrl->m_isOK && m_QRCodeUrl->m_isStartPaint && m_QRCodeUrl->m_OkNum < m_AllNum)
       {
    m_QRCodeUrl->m_isOK = true;
    //下面是一些设置
    margin = 0;
    foreground = QColor("black");
    background = QColor("white");
    casesen = true;
    mode = MODE_8;
    level = LEVEL_Q;
    percent = 0.23;

    //----------------------------

    //QWidget::paintEvent (event);
    QSize size(m_width,m_width);

    //下面一段是生成二维码图片
    QImage image(size,QImage::Format_ARGB32); //以ARGB32格式构造一个QImage,
    QPainter painter(&image);

    QRcode *qrcode = QRcode_encodeString(text.data (), 0, (QRecLevel)level, (QRencodeMode)mode, casesen ? 1 : 0);

   if(0 != qrcode) {
        unsigned char *point = qrcode->data;
        double scale = (m_width - 2.0 * margin) / qrcode->width;

        //painter.setPen(Qt::NoPen);
        painter.setBrush(this->background);
        painter.drawRect(0, 0, m_width, m_width);
        painter.setBrush(this->foreground);
        for (int y = 0; y < qrcode->width; y ++) {
            for (int x = 0; x < qrcode->width; x ++) {
                if (*point & 1) {
                    QRectF r(margin + x * scale , margin + y * scale, scale, scale);
                    painter.drawRects(&r, 1);
                }
                point ++;
            }
        }

        // painter.drawText(image.rect(),Qt::AlignCenter,"Hello");
         //将Hello写在Image的中心
        int n = 100;//这个为图片的压缩度。0/100
        image.save(m_QRCodeUrl->m_Path + "/" + pinName +".png","PNG",n);
        point = NULL;
        QRcode_free(qrcode);

    }
    qrcode = NULL;

    //下面一段是在QLabel上生成二维码
     QPainter painter_QLabel(this);
     QRcode *qrcode1 = QRcode_encodeString(text.data (), 0, (QRecLevel)level, (QRencodeMode)mode, casesen ? 1 : 0);
   if(0 != qrcode1) {
        unsigned char *point = qrcode1->data;
        double scale = (m_width - 2.0 * margin) / qrcode1->width;

        painter_QLabel.setBrush(this->background);
        painter_QLabel.drawRect(0, 0, m_width, m_width);
        painter_QLabel.setBrush(this->foreground);
        for (int y = 0; y < qrcode1->width; y ++) {
            for (int x = 0; x < qrcode1->width; x ++) {
                if (*point & 1) {
                    QRectF r(margin + x * scale , margin + y * scale, scale, scale);
                    painter_QLabel.drawRects(&r, 1);
                }
                point ++;
            }
        }

        m_QRCodeUrl->m_OkNum++;
        point = NULL;
        QRcode_free(qrcode1);

    }

    qrcode1 = NULL;
    }

    m_QRCodeUrl->m_isOK = false;
    event->accept ();
}
