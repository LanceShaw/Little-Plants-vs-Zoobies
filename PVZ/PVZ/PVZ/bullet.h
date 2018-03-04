#ifndef BULLET_H
#define BULLET_H

#include "QLabel"
#include "QImage"
#include "QPropertyAnimation"
#include "QMovie"

class Bullet:public QLabel
{
    Q_OBJECT
public:

    Bullet(QWidget* parent=0);
    int damage{20};
    QImage *bulletFlyImg;
    QPropertyAnimation *bulletAnimation;
    QMovie *movie_bulletExplosion;
    void bulletExplode();//子弹爆炸的函数

public slots:
    void slot_deleteBullet();

};

#endif // BULLET_H
