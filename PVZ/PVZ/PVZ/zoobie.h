#ifndef ZOOBIE_H
#define ZOOBIE_H

#include "QLabel"
#include "QTimer"
#include "QMovie"
#include "QMediaPlayer"

class Zoobie:public QLabel
{
    Q_OBJECT
public:

    explicit Zoobie(QWidget* parent=0);

    int life{200};//生命值
    int row{-1};//记录所在行,僵尸不用关心列
    double posX{900.0};//位置的x坐标(初始为1000)
    double posY{0};//位置的y坐标(初始为0)
    double movingSpeed{0.2};//普通僵尸4.7秒走一格（82个像素点），一秒17.5个像素点，一秒刷新50次，一次0.35个像素点
    int damageNumber{2};//100每秒,每秒刷新50次，每刷新一次造成2点伤害
    bool isEatingPlants{false};//记录是否在吃植物

    QTimer *zoobieTimer;//每个zoobie都有自己的timer
    QMovie *zoobieMoveMovie;//zoobie走路时的动作
    QMovie *zoobieEatingMovie;//zoobie吃东西时的动作

    QMediaPlayer *mediaPlayer_zoobieEating;

public slots:
    void slot_zoobiePositionChange();//位置改变
    void slot_zoobieActionChange();//动作改变

};

#endif // ZOOBIE_H
