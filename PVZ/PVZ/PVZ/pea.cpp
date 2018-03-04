#include "pea.h"
#include "globalvariable.h"

Pea::Pea(QWidget* parent):Plant(parent)
{
    pointer = parent;
    //所有植物类的共有信息
    life = 300;
    price = 100 ;
    coolingTime = 7500;

    numOfSun = numOfSun - price;//修改阳光值

    //动画设置
    plantSwingMovie = new QMovie(":/new/Pea/Peashooter.gif");
    this->setMovie(plantSwingMovie);
    plantSwingMovie->start();
    this->show();//显示豌豆动画

    //发射时间器设置
    shootingTriggerTimer = new QTimer(this);
    shootingTriggerTimer->setInterval(1400);
    shootingTriggerTimer->start();
    QObject::connect(shootingTriggerTimer,SIGNAL(timeout()),this,SLOT(slot_shootingBullet()));//每1.4秒发射一个子弹

}


void Pea::slot_shootingBullet()
{
    if(isAttacking == true)
    {
        Bullet *tempBullet = new Bullet(pointer);
        tempBullet->bulletAnimation = new QPropertyAnimation(tempBullet,"geometry");
        tempBullet->bulletAnimation->setDuration(3000);
        tempBullet->bulletAnimation->setStartValue(QRect(120 + 82*col + 80, 80 + row*100 +10,36,34));
        tempBullet->bulletAnimation->setEndValue(QRect(120 + 82*col + 80 + 900, 80 + row*100 +10,36,34));
        tempBullet->bulletAnimation->start();
        tempBullet->show();
        bulletList << tempBullet;
    }
}
