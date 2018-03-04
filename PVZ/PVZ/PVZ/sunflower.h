#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "plant.h"
#include "QTimer"

class SunFlower : public Plant
{
    Q_OBJECT
public:

    explicit SunFlower(QWidget *parent = 0);

    //向日葵特性
    const int produceSunshineInterval{10000};//生产阳光的间隔
    SunShine *sunFlower_sunshine;//自己产生的阳光
    QTimer *sunFlowerSunshineTimer;//自己生产阳光对应的时间计时器

public slots:

    void slot_produceSunshine();

};

#endif // SUNFLOWER_H
