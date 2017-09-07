#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>

#include "writeQRCode.h"
#include "QRCodeUrl.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        void                Init();
        void                makeFinish();
        void                selectFile();

    public:
         QTimer*            m_pTimer;
         //int                save_num;

    private:
        Ui::MainWindow * ui;
        writeQRCode*        m_writeQRCode;
        QRCodeUrl*          m_QRCodeUrl;

    private slots:
        void                slot_refresh();
        void on_set_start_clicked();
        void on_show_stop_clicked();
        void on_finish_goback_clicked();
        void on_set_path_click_clicked();
};

#endif // MAINWINDOW_H
