#ifndef BULLET_H
#define BULLET_H
#include <QPainter>
#include <QPixmap>
#include <QObject>
#include <QPoint>
#include "myobject.h"
#include "mywindow.h"

class Bullet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint currpos READ getCurrentPos WRITE setCurrentPos)//子弹动态移动
public:
    Bullet(QPoint startbulletpos,QPoint endbulletpos,QString path,Myobject *);
    void draw(QPainter * painter)const;
    void move();
    QPoint getCurrentPos();
    void setCurrentPos(QPoint pos);
private:
    QPoint startpos;//子弹开始位置
    QPoint endpos;//子弹结束位置
    QPoint currpos;//子弹现在位置
    QString bulletpath;//子弹图片路径
    Myobject *attenemy;//正在攻击的敌人
signals:
    void Bullet_Remove_signal(Bullet *);
    void enemy_Blood_volume_signal(Myobject *);
public slots:
    void hitTarget();//判断子弹是否击中敌人，击中则子弹消失
};

#endif // BULLET_H
