#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MyServer p(argc);

//p.doConnect();
//p.StartServer();
    MainWindow w;
   w.show();
    return a.exec();
    return 0;
}
