#include <QCoreApplication>
#include "gameserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GameServer gameServer;
    gameServer.awaitConnection();
    return a.exec();
}
