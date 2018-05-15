#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    redSound  = new QSound(":/sounds/red.wav",  this);
    blueSound = new QSound(":/sounds/blue.wav", this);

    connect(&gameModel, SIGNAL(setProrgessBarRange(int,int)), this->ui->progressBar, SLOT(setRange(int,int)));
    connect(&gameModel, SIGNAL(setProrgessBarValue(int)), this->ui->progressBar, SLOT(setValue(int)));

    connect(&gameModel, SIGNAL(gameStarted()), this, SLOT(gameStarted()));
    connect(&gameModel, SIGNAL(gameStoped()), this, SLOT(gameStoped()));

    connect(&gameModel, SIGNAL(clickButton(int)), this, SLOT(clickButton(int)));
    connect(&gameModel, SIGNAL(clickButton(int)), &gameModel, SLOT(makeMove(int)));

    connect(this->ui->startButton,SIGNAL(clicked()), &gameModel, SLOT(newGame()));

    connect(this->ui->redButton,  SIGNAL(clicked()), this, SLOT(redButtonClicked  ()));
    connect(this->ui->blueButton, SIGNAL(clicked()), this, SLOT(blueButtonClicked ()));

}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::gameStarted()
{
    this->ui->startButton->setText("Restart");
}

void MainWindow::gameStoped()
{

}

void MainWindow::clickButton(int color)
{
    switch (color) {
    case 0:
        this->ui->redButton->click();
        break;
    case 1:
        this->ui->blueButton->click();
        break;
    default:
        break;
    }
}

void MainWindow::redButtonClicked()
{
    redSound->play();
}

void MainWindow::blueButtonClicked()
{
    blueSound->play();
}

void MainWindow::on_debugComputerMove_clicked()
{
    gameModel.initialeComputerMoves();
}
