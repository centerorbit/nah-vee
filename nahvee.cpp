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

#include "nahvee.h"

#define GRAPHIC_WIDTH   90
#define GRAPHIC_HEIGHT  70
#define TOTAL_FRAMES    6
#define FRAME_DELAY      62
#define PI  3.14159
#define VELOCITY 300


Nahvee::Nahvee(QWidget *parent) :
    QWidget(parent)
{
    createSprites();

    scene = new QGraphicsScene(QRectF(0,0, GRAPHIC_WIDTH, GRAPHIC_HEIGHT));
    currentItem = 0;
    currentDirection = nahveeLeft;
    lastItem = qgraphicsitem_cast<QGraphicsItem*>(scene->addPixmap(currentDirection[currentItem++]));
    QGraphicsView* view =  new QGraphicsView(scene);
    QLayout* layout=new QVBoxLayout();
    layout->setMargin(0);
    layout->setGeometry(QRect(0,0, GRAPHIC_WIDTH, GRAPHIC_HEIGHT));
    view->setFixedSize(GRAPHIC_WIDTH, GRAPHIC_HEIGHT);
    this->setFixedSize(GRAPHIC_WIDTH, GRAPHIC_HEIGHT);

    layout->addWidget(view);
    this->setLayout(layout);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background:transparent; border: transparent;");

    runAnimation();
}

void Nahvee::nextFrame(){
    scene->removeItem(lastItem);

    if(currentItem>=currentDirection.length())
	currentItem = 0;

    lastItem = qgraphicsitem_cast<QGraphicsItem*>(scene->addPixmap(currentDirection[currentItem++]));
}

void Nahvee::move(){
    QPoint currentPos = QPoint();
    QPoint newPos = QPoint();

    currentPos = this->pos();
    newPos = QCursor::pos();
    setDestination(newPos.x(), newPos.y());

    if(reachedDestination())
            return;

    PosX += ((cos(Direction*(PI/180))*1.5)*VELOCITY/100);
    PosY += ((sin(Direction*(PI/180))*1.5)*VELOCITY/100);

    if(Direction > 90 && Direction < 270)
        currentDirection = nahveeLeft;
    else
        currentDirection = nahveeRight;

    this->setGeometry(PosX+5, PosY+5,this->width(), this->height());
}

bool Nahvee::reachedDestination(){
        double Base, Height;

        Base = DestinationX - PosX;
        Height = DestinationY - PosY;

        if ((int)Base < 30 && (int)Base > -30)
                if ((int)Height < 30 && (int)Height > -30){
                    return true;
                }

        return false;
}

void Nahvee::calcDirection(){
        double Base, Height, Hypotenuse;

        Base = DestinationX - PosX;
        Height = DestinationY - PosY;

        if(reachedDestination())
                return;

        Hypotenuse = sqrt(pow(Base, 2) + pow(Height, 2));
        Direction = asin(Height/Hypotenuse)*(180/PI);
        if (Base < 0){
                Direction = 180 - Direction;
        }

        if (Direction < 0 )
                Direction = Direction + 360;
}

void Nahvee::setDestination(int x, int y){
        DestinationX = x;
        DestinationY = y;

        calcDirection();
}



void Nahvee::runAnimation(){
    frameTimer =  new QTimer(this);
    connect(frameTimer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    frameTimer->start(62);

    moveTimer =  new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(20);
}

void Nahvee::createSprites(){
/*
	Spritesheet image was orgionally grabbed from Nintendo's Ocarina of Time 3DS Japanese website.
	http://www.nintendo.co.jp/3ds/aqej/#/
		http://www.nintendo.co.jp/3ds/aqej/img_cmn/common/navi_anime.png
	http://zelda.com/ocarina3d/
*/

    QPixmap spriteSheet = QPixmap(":/navi_sprite_sheet.png");

    for (int i = 0; i<TOTAL_FRAMES; i++){
	nahveeLeft.push_back(spriteSheet.copy(0,GRAPHIC_HEIGHT*i, GRAPHIC_WIDTH, GRAPHIC_HEIGHT));
    }
    for (int i = 0; i<TOTAL_FRAMES; i++){
	nahveeRight.push_back(spriteSheet.copy(GRAPHIC_WIDTH,GRAPHIC_HEIGHT*i, GRAPHIC_WIDTH, GRAPHIC_HEIGHT));
    }
}

Nahvee::~Nahvee()
{

}
