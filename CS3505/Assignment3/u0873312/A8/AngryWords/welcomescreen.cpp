#include "welcomescreen.h"
#include "ui_welcomescreen.h"
#include <iostream>

WelcomeScreen::WelcomeScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WelcomeScreen)
{
    ui->setupUi(this);

    // Button Connections
    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(playButtonClicked()));
    connect(ui->guestButton, SIGNAL(clicked(bool)), this, SLOT(guestButtonClicked()));
    connect(ui->playGameButton, SIGNAL(clicked(bool)), this, SLOT(playGameMainClicked()));

    // Gamewindow setup
    gameWindow = new GameWindow();
    gameWindow->setEnabled(false);

    // Hide main menu items
    ui->welcomeLabel->hide();
    ui->permissionLabel->hide();
    ui->userLabel2->hide();
    ui->playGameButton->hide();

    //Game Screen Connections
    connect(this, SIGNAL(playGame()), gameWindow, SLOT(startGame()));

    // Background setup
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,800,580);
    this->ui->welcomeGraphic->setScene(scene);
    this->ui->welcomeGraphic->setBackgroundBrush(QBrush(QPixmap(":/graphics/graphics/angry.png")));
}

WelcomeScreen::~WelcomeScreen()
{
    delete ui;
}

void WelcomeScreen::playButtonClicked()
{
    //TODO: Handle Login info.

    // Close welcome window and start game
    QString username = ui->usernameTextbox->text();
    QString password = ui->passwordTextbox->text();
    QString serverIp = ui->serverText->text();

    //emit playGame();
    //gameWindow->show();
    //gameWindow->activateWindow();
    gameWindow->m_server->sendToServer(username, password, "qweqw", "qwe");
    //this->setEnabled(false);
    //this->hide();
    //this->close();
    mainMenuDisplay(username);
}
// Use for testing without login data
void WelcomeScreen::guestButtonClicked()
{
    // Close welcome window and start game
    //emit playGame();
    //gameWindow->show();
    //gameWindow->activateWindow();
    gameWindow->m_server->sendToServer("GUEST", "12345", "sdsd", "qw");
    //this->setEnabled(false);
    //this->hide();
    //this->close();
    mainMenuDisplay("Guest");
}
void WelcomeScreen::mainMenuDisplay(QString username)
{
    // Hide login screen components.
    ui->guestButton->hide();
    ui->playButton->hide();
    ui->passwordTextbox->hide();
    ui->usernameTextbox->hide();
    ui->serverText->hide();
    ui->userLabel->hide();
    ui->passLabel->hide();
    ui->serverLabel->hide();

    // show/update main menu items
    ui->welcomeLabel->show();
    ui->permissionLabel->show();
    ui->userLabel2->show();
    ui->loggedInAs->setText(username);
    ui->permissionLevel->setText("Student");
    ui->playGameButton->show();
}
void WelcomeScreen::playGameMainClicked()
{
    // Close welcome window and start game
    emit playGame();
    gameWindow->show();
    gameWindow->activateWindow();
    this->setEnabled(false);
    this->hide();
    this->close();
}
