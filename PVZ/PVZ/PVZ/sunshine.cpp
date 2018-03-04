#include "sunshine.h"
#include "globalvariable.h"

SunShine::SunShine(QWidget *parent):QLabel(parent)
{
    sunShineMovie = new QMovie(":/new/Sunshine/Sun.gif");
    this->setMovie(sunShineMovie);

    sunShineMovie->start();

}

void SunShine::slot_changeScaledContents()
{
    this->setScaledContents(false);
}
void SunShine::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if(isCollected == false)
        {
            isCollected = true;
            numOfSun = numOfSun + 25;

            this->setScaledContents(true);
            sunShineAnimation = new QPropertyAnimation(this,"geometry");
            sunShineAnimation->setDuration(500);
            sunShineAnimation->setStartValue(QRect(this->x(),this->y(),82,100));
            sunShineAnimation->setEndValue(QRect(190,10,0,0));
            sunShineAnimation->start();
            QObject::connect(sunShineAnimation,SIGNAL(finished()),this,SLOT(slot_changeScaledContents()));

        }
    }
}
