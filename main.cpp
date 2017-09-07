#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*
     * 调用外部的qss文件
     *
     */
    QFile styleSheet(":/qss/qss/ui.qss");
    if (!styleSheet.open(QIODevice::ReadOnly))
    {
        QMessageBox::about(NULL, "warning", "Open qss failed");
    }
    QString readAllstr = styleSheet.readAll();
    qApp->setStyleSheet(readAllstr);
    styleSheet.close();

    MainWindow w;
    w.show();

    return a.exec();
}
