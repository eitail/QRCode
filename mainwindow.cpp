#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_QRCodeUrl = QRCodeUrl::getInstance();

    Init();
    //设置定时器，生成二维码
    m_pTimer  = new QTimer(this);
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(update()));
    connect(m_pTimer,SIGNAL(timeout()),this,SLOT(slot_refresh()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    //set window size
    setMinimumSize(500, 800);
    setMaximumSize(500, 800);

    //set Title
    ui->Title->setGeometry(0,0,500,50);
    ui->Title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    //set tabWidget
    ui->tabWidget->setGeometry(0,50,1500,750);
    //set set page
    ui->set_size_name->setGeometry(30,30,50,30);
    ui->set_size->setGeometry(80,30,150,30);
    ui->set_size_px->setGeometry(240,30,150,30);

    ui->set_start->setGeometry(340,30,90,90);

    ui->set_num_name->setGeometry(30,90,50,30);
    ui->set_num->setGeometry(80,90,150,30);

    ui->set_path_name->setGeometry(30,150,70,30);
    ui->set_path->setGeometry(110,150,450,30);
    ui->set_path_click->setGeometry(30,210,100,30);

    ui->set_content_name->setGeometry(30,270,50,30);
    ui->set_content->setGeometry(80,270,350,200);

    //set show page
    ui->show_stop->setGeometry(340,30,90,90);
    ui->show_plain_text->setGeometry(30,30,150,30);
    ui->shoe_cipher_text->setGeometry(30,90,150,30);
    ui->show_dis->setGeometry(30,150,150,30);
    ui->show_num->setGeometry(30,210,150,30);
    ui->show_qrcode->setGeometry(60,270,500,350);

    //set finish page
    ui->finish_num->setGeometry(0,30,500,300);
    ui->finish_num->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->finish_goback->setGeometry(200,330,100,30);

}

/**
 * @brief 点击开始按钮槽函数
 */
void MainWindow::on_set_start_clicked()
{
    m_QRCodeUrl->m_Num          = (ui->set_num->text() != "")? ui->set_num->text().toInt() : 1;
    m_QRCodeUrl->m_OkNum        = 0;
    m_QRCodeUrl->m_QrCode_w_h   = ui->set_size->currentText().toInt();
    m_QRCodeUrl->m_Url          = ui->set_content->toPlainText();
    m_QRCodeUrl->m_isStartPaint = true;
    m_QRCodeUrl->m_isOK         = false;

    if( m_QRCodeUrl->m_Path == "" )
    {
        QMessageBox::about(NULL, "提示", "请选择二维码保存路径！再点击开始！");
    }
    else
    {
        bool havePath = true;
        //----------判断存储文件夹是否存在，不存在需要创建--------
        QDir dir(m_QRCodeUrl->m_Path);
        if(!dir.exists())
        {
            if(!dir.mkpath(m_QRCodeUrl->m_Path))//创建多级目录
            {
                havePath = false;
                QMessageBox::about(NULL, "提示", "存储二维码的文件夹不存在，请重新选择，在点击开始！");
            }
        }

        if(havePath)
        {
            slot_refresh();
            m_pTimer->start(1000);
            ui->tabWidget->setCurrentIndex(1);
        }
    }
}

/**
 * @brief MainWindow::第二个界面显示的内容
 */
void MainWindow::slot_refresh()
{
    ui->show_plain_text->setText("明文：" + m_QRCodeUrl->m_text_p );
    ui->shoe_cipher_text->setText("密文：" +  m_QRCodeUrl->m_text_c );
    ui->show_dis->setText("(二维码是由密文生成)");
    ui->show_num->setText("("+ QString::number(m_QRCodeUrl->m_OkNum) + "/" + QString::number(m_QRCodeUrl->m_Num)+")");

    //如果生成的二维码张数和设置的张数相同，就停止计时器
    if( m_QRCodeUrl->m_OkNum == m_QRCodeUrl->m_Num )
    {
        makeFinish();
    }

}

/**
 * @brief 停止计时器，第三个界面展示，显示相关信息
 * m_pTimer->isActive()：判断定时器是否在工作
 */
void MainWindow::makeFinish()
{
    if(m_pTimer->isActive())
    {
        m_pTimer->stop();
    }

    ui->finish_num->setText("已完成" + QString::number(m_QRCodeUrl->m_OkNum) + "张二维码的生成！");
    ui->tabWidget->setCurrentIndex(2);
}


/**
 * @brief 点击停止按钮槽函数
 */
void MainWindow::on_show_stop_clicked()
{
    makeFinish();
}

/**
 * @brief 返回首页，所有变量都初始化
 */
void MainWindow::on_finish_goback_clicked()
{
    //QRCodeUrl清空
    m_QRCodeUrl->m_Url          = "";
    m_QRCodeUrl->m_Num          = 0;
    m_QRCodeUrl->m_OkNum        = 0;
    m_QRCodeUrl->m_QrCode_w_h   = 0;
    m_QRCodeUrl->m_isStartPaint = false;
    m_QRCodeUrl->m_text_c         = "";

    ui->show_plain_text->setText("");
    ui->shoe_cipher_text->setText("");
    ui->show_dis->setText("");
    ui->show_num->setText("");

    ui->tabWidget->setCurrentIndex(0);
}

/**
 * @brief 选择保存文件夹路径代码
 */
void MainWindow::selectFile()
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("选择文件夹"));
    fileDialog->setDirectory(".");
    m_QRCodeUrl->m_Path = fileDialog->getExistingDirectory();
    ui->set_path->setText(m_QRCodeUrl->m_Path);
}

/**
 * @brief 点击设置保存路径按钮槽函数
 */
void MainWindow::on_set_path_click_clicked()
{
     selectFile();
}
