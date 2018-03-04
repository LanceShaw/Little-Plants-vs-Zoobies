#include "bullet.h"

Bullet::Bullet(QWidget *parent):QLabel(parent)
{
    //设置子弹飞行图片图片
    bulletFlyImg = new QImage(":/new/bullet/bullet.png");
    this->setPixmap(QPixmap::fromImage(*bulletFlyImg));
    this->show();
    //设置子弹爆炸图片
    movie_bulletExplosion = new QMovie(":/new/bullet/PeaBulletHit.gif");

}

void Bullet::bulletExplode()
{
    this->setMovie(movie_bulletExplosion);
    movie_bulletExplosion->start();
    QObject::connect(movie_bulletExplosion,SIGNAL(finished()),this,SLOT(slot_deleteBullet()));
}

void Bullet::slot_deleteBullet()
{
    delete this;
}
