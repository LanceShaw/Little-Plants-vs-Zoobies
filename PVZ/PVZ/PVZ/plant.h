#ifndef PLANT_H
#define PLANT_H

#include "QLabel"
#include "sunshine.h"
#include "QMovie"
#include "QMediaPlayer"

class Plant : public QLabel
{
    Q_OBJECT
public:
    explicit Plant(QWidget* parent=0);

    //所有植物的共有性质（以向日葵的数值作为default值）
    int life{300};
    int price{50};//所耗阳光
    int coolingTime{7500};//种植一个后的冷却时间
    int row{-1};
    int col{-1};//位置信息
    int bloodDecrease{2};
    bool isBeingEaten{false};//记录是否正在被吃,初始是没有被吃的状态
    QMediaPlayer *mediaPlayer_plant;//种植植物的声音

    //所有植物的共同动画
    QMovie* plantSwingMovie;

};

#endif // PLANT_H
