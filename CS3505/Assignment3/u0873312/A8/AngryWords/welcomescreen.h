#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QImage>
#include "gamewindow.h"
#include <QWidget>

namespace Ui {
class WelcomeScreen;
}

class WelcomeScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit WelcomeScreen(QWidget *parent = 0);
    ~WelcomeScreen();
    void mainMenuDisplay(QString username);


public slots:
    void playButtonClicked();
    void guestButtonClicked();
    void playGameMainClicked();

signals:
    void playGame();

private:
    Ui::WelcomeScreen *ui;
    QGraphicsScene* scene;
    GameWindow *gameWindow;
};

#endif // WELCOMESCREEN_H
