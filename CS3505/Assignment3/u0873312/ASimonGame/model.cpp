#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "model.h"


Model::Model(QWidget *parent) : QWidget(parent)
{
    gameStatus = false;
    srand(time(NULL));      // seed for random number generator
    NumberOfButtons = 2;    // by default there are 2 botton: red and blue
    moveTimeInterval = 2000;
}


void Model::newGame(int n)
{
    if (n > 0)
        NumberOfButtons = n;
    else
        NumberOfButtons = 1;

    sequence.resize(0);
    gameStatus = true;
    gameStarted();
    initialeComputerMoves();
}

void Model::stopGame()
{
    gameStatus = false;
}

void Model::computerMakesMove()
{
    sequence.push_back(rand()%NumberOfButtons);
    iterator = sequence.begin();
}

bool Model::makeMove(int move)
{
    if(gameStatus)
    {
        gameStatus &= ((move < NumberOfButtons) && (move >= 0));
        if(iterator < sequence.end())
        {
            gameStatus &= (*iterator == move);
            ++iterator;
            setProrgessBarValue(iterator - sequence.begin());
        }
        else
        {
            sequence.push_back(move);
            setProrgessBarValue(sequence.size());
            //TODO: End of player input sequence
        }
    }
    return gameStatus;
}

const std::vector<int>& Model::getMoves() const
{
    return sequence;
}


bool Model::checkGameStatus() const
{
    return gameStatus;
}

void Model::initiateMoves()
{
    setProrgessBarRange(0, sequence.size() + 1);
    setProrgessBarValue(0);
    iterator = sequence.begin();
}

void Model::initialePlayerMoves()
{
    initiateMoves();
}

void Model::initialeComputerMoves()
{
    initiateMoves();
    timer = new QTimer();
    timer->setInterval(moveTimeInterval / 4);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(timedComputerMove()));
    timer->start();
}

void Model::timedComputerMove()
{
    if(iterator < sequence.end())
    {
        clickButton(*iterator);
    }
    else
    {
        clickButton(rand() % NumberOfButtons);
        timer->stop();
        delete timer;
    }

}
