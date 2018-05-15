#ifndef ANGRYWORD_H
#define ANGRYWORD_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QString>

class AngryWord : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QString m_word;

public:
    AngryWord(QString word);

    void typedWord(QString word);
    QString word();
public slots:
    void move();
};

#endif // ANGRYWORD_H
