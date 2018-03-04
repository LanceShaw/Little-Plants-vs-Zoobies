#ifndef PEA_H
#define PEA_H

#include "plant.h"
#include "bullet.h"
#include "QList"
#include "QTimer"

class Pea : public Plant
{
    Q_OBJECT
public:
    Pea(QWidget* parent=0);
    QWidget* pointer;
    //特有性质
    bool isAttacking{false};//是否正在攻击
    int attackNumber{20};//每颗豌豆攻击力20
    QTimer *shootingTriggerTimer;//控制发射豌豆间隔
    QList<Bullet*> bulletList;//子弹的一个List

public slots:
    void slot_shootingBullet();
};

#endif // PEA_H
