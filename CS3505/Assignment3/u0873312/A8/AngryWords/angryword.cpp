#include <QTimer>
#include <QPainter>
#include "angryword.h"

AngryWord::AngryWord(QString word)
{
    m_word = word;

    const int letterWidth = 12;
    const int letterHeight = 18;

    setPos(700,100);
    QPixmap myPixmap(":/graphics/graphics/word_background.png");
    myPixmap = myPixmap.scaled(letterWidth * m_word.size() + 10, letterHeight * 1.5);
    QPainter painter(&myPixmap);
    painter.setFont(QFont("Arial",letterHeight,4));
    painter.setPen(QColor(255,255,255));
    painter.drawText(5, 18, m_word);
    setPixmap(myPixmap);


    QTimer* timer = new QTimer(this);
    timer->setInterval(250);

    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start();

}

void AngryWord::typedWord(QString word)
{
    if(word == m_word)
    {
        delete this;
    }
}

QString AngryWord::word()
{
    return m_word;
}

void AngryWord::move()
{
    setPos(x()-5,y());
}
