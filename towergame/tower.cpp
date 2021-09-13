#include <QDebug>
#include <QtMath>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QTimer>
#include "towerpos.h"
#include "bullet.h"
#include "tower.h"
Tower::Tower(QPoint pos,MyWindow* mygame,QString path):QObject(nullptr),pixmap(path)
{
    _pos = pos;
    game = mygame;
    choseenemy = nullptr;
    towerrank = First_tower_rand;
    tower_Range = First_tower_range;
    ifenemy = false;//判断是否有可攻击的敌人
    ifrange = false;//判断塔范围内是否有敌人
    m_fireRate = 1000;//定时器时间间隔1s
    m_fireRateTime = new QTimer(this);
    connect(m_fireRateTime,&QTimer::timeout,this,[=](){
        shootWeapon();
    });
    m_fireRateTime->start(m_fireRate);
}
//判断敌人是否在塔范围内，俩点之间的距离
bool Tower::collisionWithCircle(QPoint p1,int r1,QPoint p2,int r2)
{
    int xx=p1.x()-p2.x();
    int yy=p1.y()-p2.y();
    int dis=int(sqrt(xx*xx+yy*yy));
    if(dis<r1+r2)
    {
        return true;
    }
    return false;
}
//隔一秒时间获取敌人当前的位置
void Tower::shootWeapon()
{
    if(ifrange)//该防御塔范围内有敌人才能创建子弹
    {
        Bullet *bullet = new Bullet(_pos,choseenemy->currentPos,":/bullet.png",choseenemy);
        bullet->move();
        game->addbullet(bullet);
    }
}

//不断刷新敌人移动的位置，以便获取
void Tower::checkEnemyInRange()
{
        if(ifenemy)//如果有了攻击的敌人
        {
            if(!collisionWithCircle(_pos,tower_Range+20,choseenemy->currentPos,1))//当敌人不在范围内的时候
            {
                ifenemy = false;//设置为没有可攻击的敌人
            }
        }
        else
        {
            //如果没有攻击的敌人，就遍历enemylist，找到在攻击范围内的敌人
            QList<Myobject * > enemyList=game->myobject_list;
            qDebug()<<QStringLiteral("敌人的个数")<<game->myobject_list.count();
            foreach(Myobject * enemy,enemyList)
            if(collisionWithCircle(_pos,tower_Range+20,enemy->currentPos,1))//是否在塔范围内
            {
                choseenemy = enemy;
                ifenemy = true;
                ifrange = true;
                break;
            }
            else
            {
                ifrange = false;
            }
        }
}

void Tower::draw(QPainter *painter)const
{
    painter->save();
    painter->setPen(Qt::green);
    Towerpos *towerpos = nullptr;//调用防御塔坑的图片的宽度和高度
    if(towerrank == First_tower_rand)
    {
        painter->drawPixmap(_pos.x()-towerpos->m_fixedSize.width()/2,_pos.y()-towerpos->m_fixedSize.height()/2,QPixmap(":/tower2.gif"));
        painter->drawEllipse(_pos,First_tower_range,First_tower_range);//画出防御塔的攻击范围
    }
    if(towerrank == Second_tower_rand)
    {
        painter->drawPixmap(_pos.x()-towerpos->m_fixedSize.width()/2,_pos.y()-towerpos->m_fixedSize.height()/2,QPixmap(":/tower3.gif"));
        painter->drawEllipse(_pos,Second_tower_range,Second_tower_range);//画出防御塔的攻击范围
    }
    if(towerrank == Three_tower_rand)
    {
        painter->drawPixmap(_pos.x()-towerpos->m_fixedSize.width()/2,_pos.y()-towerpos->m_fixedSize.height()/2,QPixmap(":/tower4.gif"));
        painter->drawEllipse(_pos,Three_tower_range,Three_tower_range);//画出防御塔的攻击范围
    }
}
