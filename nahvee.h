/*
Copyright (c) 2012 Andrew LeTourneau

Permission is hereby granted, free of charge, to any person obtaining 
a copy of this software and associated documentation files (the "Software"), 
to deal in the Software without restriction, including without limitation the 
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions: 

The above copyright notice and this permission notice shall be included in 
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
IN THE SOFTWARE.
*/

#ifndef NAHVEE_H
#define NAHVEE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QGraphicsItem>
#include <QTimer>
#include <QSound>
#include <math.h>



class Nahvee : public QWidget
{
    Q_OBJECT

public:
    explicit Nahvee(QWidget *parent = 0);

    ~Nahvee();

private:
    void createSprites();
    void runAnimation();
    QTimer *frameTimer;
    QTimer *moveTimer;
    QTimer *heyListenTimer;
    QList<QPixmap> nahveeLeft;
    QList<QPixmap> nahveeRight;
    QList<QPixmap> currentDirection;
    QGraphicsScene* scene;
    QGraphicsItem* lastItem;
    QSound* heyListen;
    int currentItem;
    void calcDirection();
    bool reachedDestination();
    void calcNextStep();
    void setDestination(int x, int y);

    double Direction;//a 360 degree value
    double DestinationX;
    double DestinationY;
    double PosX;
    double PosY;

private slots:
    void nextFrame();
    void move();
    void heyListenPlay();

protected:
   // void paintEvent(QPaintEvent *event);
};

#endif // NAHVEE_H
