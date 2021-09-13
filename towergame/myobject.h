#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QPoint>
#include <QPixmap>
#include <QPainter>
#include "waytower.h"

class MyWindow;

class Myobject : public QObject
{
    Q_OBJECT
public:
    Myobject(Waytower *,QString filename);
    void move();
    void draw(QPainter *painter)const;
    void doActive();//敌人是否可以移动
    QPoint currentPos;//敌人当前位置
    int currentHp;//敌人当前血量
    int maxHp;//最大血量
    QPixmap pixmap;//敌人图片路径
private:
    qreal speed;
    Waytower * m_destinationWayPoint;//目标航点的指针
    bool enemyifact;
    static const QSize enemy_fixedSize;
signals:
    void Get_to_base_signals(Myobject *);
public slots:
};

#endif // MYOBJECT_H
