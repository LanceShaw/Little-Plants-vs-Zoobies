#ifndef SUNSHINE_H
#define SUNSHINE_H

#include "QLabel"
#include "QMouseEvent"
#include "QMovie"
#include "QMouseEvent"
#include "QPropertyAnimation"

class SunShine:public QLabel
{
    Q_OBJECT
public:
    SunShine(QWidget* parent=0);
    const int sunshine_numOfSun{25};
    QMovie *sunShineMovie;
    bool isCollected{false};
    QLabel *tempSunshineLabel;
    QPropertyAnimation *sunShineAnimation;
protected:
    void mousePressEvent(QMouseEvent *event);//重写阳光的mousePressEvent
public slots:
    void slot_changeScaledContents();
};

#endif // SUNSHINE_H
