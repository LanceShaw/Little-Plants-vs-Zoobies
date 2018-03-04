#include "wallnut.h"

#include"globalvariable.h"

WallNut::WallNut(QWidget* parent):Plant(parent)
{
    //植物共有性质的赋值
    life = 4000;
    price = 50;
    coolingTime = 30000;

    numOfSun = numOfSun - price;//修改阳光值

    //动画
    plantSwingMovie = new QMovie(":/new/WallNut/WallNut.gif");
    this->setMovie(plantSwingMovie );
    plantSwingMovie ->start();
    this->show();//显示坚果动画
}




