#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QProgressBar>
#include <QtMultimedia/QSound>

#include "model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Model gameModel;
    QSound* redSound;
    QSound* blueSound;

    //sounds
    //you lose message
    //rules
    //time countdown

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    Ui::MainWindow *ui;
public slots:
    void gameStarted();                // ui response to the start of the game
    void gameStoped();                 // ui response to game over
    void clickButton(int color);       // allows the AI to press colored buttons
private slots:
    void redButtonClicked();
    void blueButtonClicked();

    void on_debugComputerMove_clicked();
};

#endif // MAINWINDOW_H
