#include "towerpos.h"

const QSize Towerpos::m_fixedSize(60,60);//设置图片的大小

Towerpos::Towerpos(QPoint pos,QString path):tow_pos(pos),tow_path(path)
{
    iftower = false;//初始化没有防御塔

}
//画出防御塔坑
void Towerpos::draw(QPainter *painter)const
{
    painter->drawPixmap(tow_pos,tow_path);
}

bool Towerpos::ContainPos(QPoint pos)//判断鼠标的位置是否和防御塔坑的位置一致
{
    bool xInHere=pos.x()>tow_pos.x() && pos.x()<tow_pos.x()+m_fixedSize.width()/2;
    bool yInHere=pos.y()>tow_pos.y() && pos.y()<tow_pos.y()+m_fixedSize.height()/2;
    return xInHere && yInHere;
}

void Towerpos::settower(Tower * tower)
{
    currtower = tower;
}

Tower *Towerpos::get_tower()
{
    return currtower;
}

