#include <QtGui/QApplication>
#include "maindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainDialog w;
    w.setWindowFlags(Qt::FramelessWindowHint);//使窗口无边框
    w.show();
    
    return a.exec();
}
