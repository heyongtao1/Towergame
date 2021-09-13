#include <QDebug>
#include <QPropertyAnimation>
#include "bullet.h"
Bullet::Bullet(QPoint startbulletpos,QPoint endbulletpos,QString path,Myobject *aimenemy):
  startpos(startbulletpos),
  endpos(endbulletpos),
  bulletpath(path)
{
    currpos = startpos;
    attenemy = aimenemy;//正在攻击的敌人
}

void Bullet::move()//动态实现子弹移动
{
    static int duration=100;
    QPropertyAnimation* animation =new QPropertyAnimation(this,"currpos");//geometry为动画属性
    animation->setDuration(duration);
    animation->setStartValue(startpos);
    animation->setEndValue(endpos);
    connect(animation,SIGNAL(finished()),this,SLOT(hitTarget()));
    //animation->setEasingCurve(QEasingCurve::CosineCurve);
    animation->start();
}
//击中敌人，子弹消失
void Bullet::hitTarget()
{
    if(attenemy->currentHp)//敌人血量减少10
    {
        attenemy->currentHp = attenemy->currentHp - 10;
    }
    else//敌人血量为0，则除去敌人
    {
       //mywindow->removeenemy(attenemy);
        emit enemy_Blood_volume_signal(attenemy);
    }
    //mywindow->removebullet(this);//击中敌人后子弹就要消失
    emit Bullet_Remove_signal(this);
}

QPoint Bullet::getCurrentPos()
{
    return currpos;
}

void Bullet::setCurrentPos(QPoint pos)
{
    currpos=pos;
}

void Bullet::draw(QPainter *painter)const
{
    painter->drawPixmap(currpos,bulletpath);
}
