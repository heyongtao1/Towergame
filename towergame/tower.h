#ifndef TOWER_H
#define TOWER_H

#include <QObject>
#include <QPixmap>
#include <QPoint>  //点的坐标头文件
#include <QTimer>
#include "myobject.h"


class MyWindow;
class Bullet;
class MyButton;

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos,MyWindow *,QString path);
    void draw(QPainter *painter)const;
    bool collisionWithCircle(QPoint p1,int r1,QPoint p2,int r2);
    void chooseEnemyFromAttack(Myobject *enemy);
    void attackEnemy();
    void shootWeapon();
    void checkEnemyInRange();
    void lostSightOfEnemy();

    Myobject *choseenemy;//选择的敌人
    QPoint _pos;
    QPixmap pixmap;
    MyWindow *game;
    QTimer *m_fireRateTime;//定时器射击
    int m_fireRate;//射速
    bool ifenemy;//判断是否有攻击的敌人
    bool ifrange;
    int towerrank;//防御塔等级
    int tower_Range ;
signals:

public slots:
};

#endif // TOWER_H
