#include "bucketzoobie.h"

BucketZoobie::BucketZoobie(QWidget *parent): Zoobie(parent)
{
    //成员变量的改变
    this->life = 1300;
    this->movingSpeed = 0.2;

    //基本动画的设置
    zoobieMoveMovie = new QMovie(":/new/bucketZoobie/BucketheadZombie.gif");
    zoobieEatingMovie = new QMovie(":/new/bucketZoobie/BucketheadZombieAttack.gif");

}
