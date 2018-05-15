#include "gameserver.h"
using namespace sf;

GameServer::GameServer(QObject *parent) : QObject(parent)
{
    m_score = 0;
    m_level = 1;
    m_dictionary = new Dictionary();
    socket.connect("127.0.0.1", 6006);
}

void GameServer::newGame()
{
    m_score = 0;
    m_level = 1;
    // start timers to spawn enemies
}

void GameServer::endGame()
{
    // destroy all the enemiers and stop all the timers
}

void GameServer::newEnemy()
{
    // spaw enemy
}

void GameServer::checkWord()
{

}

QString *GameServer::getWord()
{
    return m_dictionary->getWord();
}

void GameServer::receiveFromServer()
{
    char buffer[1024];
    std::size_t received = 0;
    socket.receive(buffer, sizeof(buffer), received);
    std::cout << "The server said: " << buffer << std::endl;
}

void GameServer::sendToServer(QString username, QString password, QString score, QString level)
{
    std::string message = "user:"+username.toStdString() + ";password:"+password.toStdString()
            + ";score:" + score.toStdString() + ";level:" + level.toStdString() + ";";
    socket.send(message.c_str(), message.size()+1);
}
