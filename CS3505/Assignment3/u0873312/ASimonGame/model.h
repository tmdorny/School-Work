#ifndef MODEL_H
#define MODEL_H

#include <QWidget>
#include <QTimer>

#include <vector>


class Model : public QWidget
{
    Q_OBJECT



public:
    explicit Model(QWidget *parent = 0);


    void computerMakesMove();                   // makes a computer to make move(assuming player finished his move)
    bool checkGameStatus() const;               // returns the value of gameStatus variable



    //vector<int> getPlayerMoves() const;
    const std::vector<int>& getMoves() const;   // returns an array of moves made by the computer during its last move

    //float getPlayersMoveProgress() const;       // returns a value from 0.0 to 1.0. 0 - player did not make a move, 1 - player complted the move

    //static bool self_test();                    // a simple usage test

private:
    int moveTimeInterval;
    std::vector<int> sequence;                   // an array that contains the current game state in terms of moves have to be made by a player
    bool gameStatus;                             // false if the game was lost or have not started yet
    int NumberOfButtons;                         // number of colored buttons in Simon Game
    std::vector<int>::const_iterator iterator;   // represents current player position;
    void initiateMoves();
    QTimer* timer;

signals:
    void clickButton(int n);
    void setProrgessBarRange(int min, int max);
    void setProrgessBarValue(int val);

    void gameStarted();
    void gameStoped();

private slots:
    void timedComputerMove();

public slots:
    void newGame(int n = 2);
    void stopGame();

    bool makeMove(int move);                    // returns true if the move as valid and makes the move
                                                // returns false if the move is not valid and finishes the game

    void initialePlayerMoves();               // This would start a countdown and wait for signals or send a signal if the game ends
    void initialeComputerMoves();             // This would start a countdown and send signals

};

#endif // MODEL_H
