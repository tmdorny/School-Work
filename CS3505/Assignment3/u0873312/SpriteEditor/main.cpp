//A7: Sprite Editor
//Author: Nick Pershyn(uNID: u0873312)
//github: LinuxUser404

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
