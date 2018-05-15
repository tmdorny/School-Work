#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    m_server = new GameServer(this);
    m_server->newGame();

    // our sound does not compile on travis and lab2, becuase of missing QtMultimedia
    //m_music  = new QSound(":/snd/saw800.wav",  this);
    connect(this->ui->actionPlay_music, SIGNAL(triggered()), this, SLOT(playMusic()));
    //connect(this->ui->actionStop_music, SIGNAL(triggered()), this, SLOT(stopMusic()));

    m_scene = new QGraphicsScene(this);
    m_scene->setSceneRect(0,0,800,450);

    //this->ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->ui->graphicsView->setScene(m_scene);
    this->ui->graphicsView->setBackgroundBrush(QBrush(QPixmap(":/graphics/graphics/background.png")));

    //setWord();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::startGame()
{
    this->setEnabled(true);
    setWord();
}

void GameWindow::setWord()
{
    m_mainWord = new AngryWord(*(m_server->getWord()));
    ui->testWord->setText(m_mainWord->word());


    /*QGraphicsPixmapItem* newWord = new QGraphicsPixmapItem();
    newWord->setPos(100,0);
    QPixmap myPixmap(":/graphics/graphics/word_background.png");
    myPixmap = myPixmap.scaled(letterWidth * m_mainWord.size(), letterHeight);
    QPainter painter(&myPixmap);
    painter.setFont(QFont("Arial",letterHeight,4));
    painter.setPen(QColor(255,255,255));
    painter.drawText(0, 18, m_mainWord);
    newWord->setPixmap(myPixmap);*/


    m_scene->addItem(m_mainWord);


}

void GameWindow::playMusic()
{

//    sf::Music music;

//    if(!music.openFromFile("/snd/saw800.wav"))
//    {
//    }
//    else
//    {
//        music.play();
//    }
}

void GameWindow::stopMusic()
{
    //m_music->stop();
}

//manages key shortcuts (color selections)
void GameWindow::keyPressEvent(QKeyEvent* e)
{
    //if the user presses space or enter, it checks their word and
    //gets a new one if its equal to the main word
    if(e->key() == Qt::Key_Space || e->key() == Qt::Key_Return)
    {
        int x = QString::compare(m_userWord, m_mainWord->word(), Qt::CaseInsensitive);
        if(x == 0)
        {
            m_scene->removeItem(m_mainWord);
            setWord();
            m_userWord = "";
        }
    }
    else if(e->key() == Qt::Key_Backspace) //backspace erases the user's word
    {
        m_userWord = "";
    }
    else
    {
        //use regualr expression to check if its a valid letter
        QRegExp re("\\w*");  // a word (\w), zero or more times (*)
        if (re.exactMatch(e->text()))
        {
            m_userWord = m_userWord + e->text();
        }
    }

    //update the label on the GUI
    ui->userWordLabel->setText(m_userWord);

    //UN-COMMENT THIS CODE FOR IN LINE TYPING
    int x = QString::compare(m_userWord, m_mainWord->word(), Qt::CaseInsensitive);
    if(x == 0)
    {
        setWord();
        m_userWord = "";

        ui->userWordLabel->setText(m_userWord);
    }
}
