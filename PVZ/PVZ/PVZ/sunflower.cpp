#include "sunflower.h"
#include "globalvariable.h"

SunFlower::SunFlower(QWidget *parent) : Plant(parent)
{
    //动画设计
    plantSwingMovie = new QMovie(":/new/SunFlower/SunFlower1.gif");
    this->setMovie(plantSwingMovie);
    plantSwingMovie->start();
    this->show();//显示向日葵动画

    numOfSun = numOfSun - price;

    //产生阳光
    sunFlower_sunshine = new SunShine(parent);//让整个窗口成为sunshine的父对象
    sunFlowerSunshineTimer = new QTimer(this);
    sunFlowerSunshineTimer->setInterval(produceSunshineInterval);
    sunFlowerSunshineTimer->start();
    QObject::connect(sunFlowerSunshineTimer,SIGNAL(timeout()),this,SLOT(slot_produceSunshine()));

}

void SunFlower::slot_produceSunshine()
{
    sunFlower_sunshine->isCollected = false;
    sunFlower_sunshine->setGeometry(120 + 82 * col , 80 + 100 * row, 82, 100);
    sunFlower_sunshine->show();
    sunFlower_sunshine->raise();
}




