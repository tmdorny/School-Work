#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <iostream>
//#include <QtMultimedia/QSound>
//#include "welcomescreen.h"

#include "dictionary.h"
#include "gameserver.h"
#include "angryword.h"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include <QtGui>


namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    void keyPressEvent(QKeyEvent* e);
    GameServer* m_server; //dictionary is private to m_server

    void setWord();

private slots:

    void playMusic();
    void stopMusic();
    void startGame();

private:
    Ui::GameWindow *ui;

    //Dictionary dictionary;
    //QSound* m_music;
    AngryWord* m_mainWord;
    QString m_userWord;
    QGraphicsScene* m_scene;
    //WelcomeScreen *welcomeScreen;

};

#endif // GAMEWINDOW_H
