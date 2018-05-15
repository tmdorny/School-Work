#include "gamewindow.h"
#include "welcomescreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //GameWindow w;
    WelcomeScreen w;
    w.show();

    return a.exec();
}
