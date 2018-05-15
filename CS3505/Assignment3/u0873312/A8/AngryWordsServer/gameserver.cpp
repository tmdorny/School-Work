#include "gameserver.h"
#include <iostream>
using namespace sf;

GameServer::GameServer()
{
    port = 6006;
}

void GameServer::awaitConnection()
{
    TcpListener listener;
    listener.listen(port);
    listener.accept(socket);
    updateDatabase();
    updateClient();
}

void GameServer::updateDatabase()
{
    char buffer[1024];
    size_t received = 0;
    socket.receive(buffer, sizeof(buffer), received);
    cout << "The client said: " << buffer << endl;
    vector<string> info = split(buffer, ';');
    string user, password, score, level;
    for(int i=0; i<info.size(); i++)
    {
        if (info[i].find("user") != string::npos)
        {
            user = info[i];
        }
        else if(info[i].find("password") != string::npos)
        {
            password = info[i];
        }
        else if(info[i].find("score") != string::npos)
        {
            score = info[i];
        }
        else if(info[i].find("level") != string::npos)
        {
            level = info[i];
        }
    }
    // Send to database
    cout << "The client said: " << user << "\n" <<
         password << "\n" << score << "\n" << level << endl;
}

void GameServer::updateClient()
{
    string message = "Welcome, client";
    socket.send(message.c_str(), message.size() + 1);
}

void GameServer::getEntireDatabase()
{

}

vector<string>& GameServer::split(const string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> GameServer::split(const string &s, char delim)
{
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
