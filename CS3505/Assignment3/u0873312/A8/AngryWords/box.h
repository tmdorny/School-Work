#ifndef BOXLIST_H
#define BOXLIST_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QObject>
#include "Box2D/Box2D.h"
#include <QtGui>


class Level: public QObject
{
    Q_OBJECT
    public:

    int health = 5;

    const float SCALE = 30.f;

    b2World* World;

    Level();

    void CreateGround(float X, float Y);

    void CreateBox(int PositionX, int PositionY);

    public slots:

    void Step();

    void Damaged();


};


#endif // BOXLIST_H
