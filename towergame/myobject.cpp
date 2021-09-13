#include <QPoint>
#include <QPixmap>
#include <QVector2D>
#include <QPainter>
#include <QDebug>
#include "towerpos.h"
#include "tower.h"
#include "mywindow.h"
#include "myobject.h"
#include <QMessageBox>
const QSize Myobject::enemy_fixedSize(60,60);//设置敌人图片的大小

Myobject::Myobject(Waytower *startwaypos,QString path) : QObject(nullptr),pixmap(path)//一定要记得初始化路径
{
  this->m_destinationWayPoint =startwaypos;
  this->speed = Game_enemy_move_speed;
  this->currentPos = m_destinationWayPoint->currpoint;
  this->enemyifact = false;
  this->maxHp = Game_enemy_maxHp;
  this->currentHp = maxHp;
}

void Myobject::move()
{
    if(currentPos == m_destinationWayPoint->nextwaypos->currpoint)
    {
        if(m_destinationWayPoint->nextwaypos->nextwaypos)//如果还存在下一个站点，这重新设置敌人的路线
        {
             currentPos = m_destinationWayPoint->nextwaypos->currpoint;//重新设置敌人当前位置坐标
             m_destinationWayPoint = m_destinationWayPoint->nextwaypos;
        }
        //到达基地
        else
        {
            emit Get_to_base_signals(this);
        }
    }
    else //还在向目标站点走的过程中
    {
        QVector2D vector(m_destinationWayPoint->nextwaypos->currpoint - m_destinationWayPoint->currpoint);//vector只是一个有方向的向量，targetPos不是做为终止运动的条件，没自定义控制终止条件是会沿着该方向一直运动下去
        vector.normalize();
        currentPos = currentPos + vector.toPoint()*speed;
    }
}

void Myobject::draw(QPainter *painter)const
{
    //下面准备绘画敌人开始最大的血条
    painter->save();//保存原本的画家笔的属性
    static const int healthBarWidth=this->enemy_fixedSize.width();//设置血条的长度
    QPoint healthBarPoint=this->currentPos+QPoint(-this->enemy_fixedSize.width()/2,-this->enemy_fixedSize.height()/2);//设置血条的左上点
    painter->setPen(Qt::NoPen);//画笔的颜色
    painter->setBrush(Qt::red);//刷子的颜色，用来填充内部
    QRect healthBarBackRect(healthBarPoint,QSize(healthBarWidth,4));//设置血条的粗细程度
    painter->drawRect(healthBarBackRect);//画出血条
    //敌人的当前血量
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint,QSize((double)currentHp/maxHp*healthBarWidth,4));
    painter->drawRect(healthBarRect);//画出当前血量血条

    painter->restore();//还原画家的笔的属性
    //绘画出敌人
    painter->drawPixmap(currentPos.x()-this->enemy_fixedSize.width()/2,currentPos.y()-this->enemy_fixedSize.height()/2,pixmap);
}

void Myobject::doActive()
{
    this->enemyifact = true;
}
