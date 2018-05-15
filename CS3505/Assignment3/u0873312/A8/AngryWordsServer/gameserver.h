#ifndef GAMESERVER_H
#define GAMESERVER_H

#include "SFML/Network.hpp"
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class GameServer
{
public:
    GameServer();
private:
    int m_score;
    int m_level;
//    Dictionary* m_dictionary;
    int port;
    sf::TcpSocket socket;

public:
    void awaitConnection();
    void updateDatabase();
    void getEntireDatabase();
    void updateClient();
    vector<string> split(const string&, char);
    vector<string> &split(const string&, char, vector<string>&);
};

#endif // GAMESERVER_H
