#ifndef WAYTOWER_H
#define WAYTOWER_H

#include <QPoint>
#include <QPainter>
#include <QPaintEvent>

class Waytower
{
public:
    Waytower(QPoint point);
    void draw(QPainter *)const;
    //Waytower * getNextWayPoint();//得到下一个航点的指针
    void setnextwaypos(Waytower *);//设置下一个站点位置

    QPoint currpoint;//当前的站点位置
    Waytower *nextwaypos;//下一个站点的指针

};

#endif // WAYTOWER_H
