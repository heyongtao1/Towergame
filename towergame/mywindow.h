#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QLabel>
#include <QMouseEvent>
#include <QList>
#include <QMediaPlayer>
#include "myobject.h"
#include "towerpos.h"
#include "waytower.h"
#include "tower.h"
#include <QPushButton>
#include "mycpp.h"
class Tower;
class Towerpos;
class Bullet;
class MyButton;

class MyWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyWindow(QMediaPlayer *);
    void paintEvent(QPaintEvent *);//该函数名不能写错，切记，该函数是次界面打开时自动调用（所以绘画显示都在该函数实现）
    ~MyWindow();
    void sett_tower(QPoint pos);//设置防御塔
    void addMyObject();//添加敌人
    void updatescene();//用定时器不断调用敌人移动函数
    void mousePressEvent(QMouseEvent * event);
    void addTowerpos();//添加防御塔坑
    void addwaytower();//添加站点
    void gameStart();//定时器控制添加敌人的槽函数
    void addbullet(Bullet *);//添加子弹
    void removebullet(Bullet *);//当击中敌人，除去子弹
    void removeenemy(Myobject *,int);//敌人死亡，除去敌人
    bool waveaddenemy();//波数控制添加敌人
    void controldraw();//控件的绘画
    void control_init();
    void Next_Level();
public slots:
    void enemy_Get_to_base(Myobject *);
    void Bullet_Remove(Bullet *);
    void enemy_Blood_volume(Myobject *);
public:
    QList<Tower*> tower_list;//存储防御塔列表
    QList<Myobject*> myobject_list;//存储敌人的列表
    QList<Towerpos *> towerpos_list;//存储防御塔坑列表
    QList<Waytower *>waytower_list;//存储站点的列表
    QList<Bullet *>bullet_list;//存储子弹的列表
    QList<Tower* >attactenemytow_list;//存储攻击敌人的所有防御塔列表
    QList<QPoint> explode_list;//敌人死亡，爆炸列表
private:
    int wavenum;//敌人出现的波数
    int monoy;//当前的金币
    QLabel *monoylabel;
    QLabel *base_Blood_label;
    QLabel *Curr_Level_label;
    QLabel *Curr_Count_label;
    QPainter *painter;
    int Curr_Level;
    int Curr_Count;
    QMediaPlayer *Curr_music;
public:
    int base_Blood_volume ;
    QTimer *timer1;
signals:
    void back_signals();//返回主界面的信号

};

#endif // MYWINDOW_H
