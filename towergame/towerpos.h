#ifndef TOWERPOS_H
#define TOWERPOS_H

#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include <QSize>
#include "tower.h"
class Towerpos
{
public:
    Towerpos(QPoint pos,QString path);
    void draw(QPainter *painter)const;
    bool ContainPos(QPoint pos);//判断pos点是否在防御塔坑的范围内
    void settower(Tower *);
    Tower *get_tower();
public:
    QPoint tow_pos;//塔坑的中心位置
    QPixmap tow_path;//塔坑的图标路径
    static const QSize m_fixedSize;//防御塔坑的固定大小
public:
    bool iftower;//判断该塔坑处是否已有防御塔
    Tower *currtower;
};

#endif // TOWERPOS_H
