#include <QDebug>
#include <QPoint>
#include <QDebug>
#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <QMediaPlaylist>
#include "myobject.h"
#include "towerpos.h"
#include "mywindow.h"
#include "mybutton.h"
#include "bullet.h"
#include "tower.h"
#include "mycpp.h"
#include <QMessageBox>
MyWindow::MyWindow(QMediaPlayer *battle_music)
{
    this->setFixedSize(800,600);
    this->setWindowTitle(QString(QStringLiteral("屠杀恶魔城大战")));
    this->setWindowIcon(QIcon(QPixmap(":/enemy5.gif")));
    wavenum = 0;//敌人出现的波数
    monoy = Game_init_money;//游戏开始时的金币
    base_Blood_volume = Game_base_Blood_volume;
    Curr_Level = First_Level;
    Curr_Count = 0;
    Curr_music = battle_music;

    addTowerpos();//调用添加塔坑函数
    addwaytower();//调用添加站点函数
    control_init();

    timer1 = new QTimer(this);
    connect(timer1,&QTimer::timeout,this,[=](){
        updatescene();//不断更新敌人、子弹移动
        controldraw();
        Next_Level();
    });
    timer1->start(First_Speed);
    QTimer::singleShot(100,this,&MyWindow::gameStart);
}
void MyWindow::control_init()
{
    MyButton *back_Bt = new MyButton(":/end.jpg");//返回主界面按钮
    back_Bt->setParent(this);
    back_Bt->move(700,40);

    MyButton *start_bt = new MyButton(":/start.jpg");//开始游戏按钮
    start_bt->setParent(this);
    start_bt->move(40,40);

    monoylabel = new QLabel();//显示当前的金币多少
    monoylabel->setParent(this);
    monoylabel->move(40,60);
    monoylabel->setFixedSize(QSize(150,40));

    base_Blood_label = new QLabel();//显示当前的基地血量
    base_Blood_label->setParent(this);
    base_Blood_label->move(40,80);
    base_Blood_label->setFixedSize(QSize(150,40));

    Curr_Level_label = new QLabel();//显示当前的关卡
    Curr_Level_label->setParent(this);
    Curr_Level_label->move(40,100);
    Curr_Level_label->setFixedSize(QSize(150,40));

    Curr_Count_label = new QLabel();//显示当前的分数
    Curr_Count_label->setParent(this);
    Curr_Count_label->move(40,120);
    Curr_Count_label->setFixedSize(QSize(150,40));

    connect(back_Bt,&MyButton::clicked,this,[=](){//将Mywindow界面上的按钮和该界面关联起来，按钮发出信号给该界面接收
        emit back_signals();
        Curr_music->stop();
    });

    connect(start_bt,&MyButton::clicked,this,&MyWindow::Next_Level);
}
//下一关
void MyWindow::Next_Level()
{
    if(Curr_Count >= Three_Count)
    {
        timer1->stop();
        QMessageBox::information(this,QStringLiteral("游戏提示"),QStringLiteral("游戏通关"));
    }
    //第二关
    if(Curr_Count == First_Count)
    {
        Curr_Level = Second_Level;
        timer1->start(Second_Speed);
        wavenum = 0;

        Curr_music->pause();
        Curr_music->playlist()->setCurrentIndex(1);
        Curr_music->play();
    }
    //第三关
    if(Curr_Count == Second_Count)
    {
        Curr_Level = Three_Level;
        timer1->start(Three_Speed);
        wavenum = 0;

        Curr_music->pause();
        Curr_music->playlist()->setCurrentIndex(2);
        Curr_music->play();
    }
}

void MyWindow::enemy_Get_to_base(Myobject *delete_enemy)
{
    //当达到终点，除去敌人,基地血量减少10
    removeenemy(delete_enemy,Game_enemy_Get_to_Base);
    if(base_Blood_volume <=0 )
    {
        //游戏结束，玩家战败
        timer1->stop();
        QMessageBox::information(this,QStringLiteral("游戏提示"),QStringLiteral("游戏失败"));
    }
    base_Blood_volume -= Game_base_Blood_loss_speed;
}

void MyWindow::Bullet_Remove(Bullet *delete_bullet)
{
    removebullet(delete_bullet);
}

void MyWindow::enemy_Blood_volume(Myobject *delete_enemy)
{
    removeenemy(delete_enemy,Game_enemy_dead);
}

//绘制界面
void MyWindow::paintEvent(QPaintEvent *)
{
   painter = new QPainter(this);
   QPixmap pixmap(":/background2.jpg");
   painter->drawPixmap(0,0,this->width(),this->height(),pixmap);//设置次界面的背景

   foreach(const Waytower *waytower, waytower_list)//遍历绘画显示站点出来
       waytower->draw(painter);

   foreach(const Myobject* object,myobject_list)//遍历敌人显示出来
       object->draw(painter);

   foreach(const Towerpos *towerpos,towerpos_list)//遍历塔坑显示出来
       towerpos->draw(painter);

   foreach(const Tower *tower,tower_list)//遍历塔坑显示出来
       tower->draw(painter);

   foreach(const Bullet* bullet,bullet_list)//遍历子弹显示出来
       bullet->draw(painter);

   foreach(const QPoint point,explode_list)//遍历死亡的敌人，爆炸显示出来
   {
       QPixmap pixmap(":/explode.png");
       painter->drawPixmap(point.x()-20,point.y()-20,40,40,pixmap);
       this->explode_list.removeOne(point);
   }

}


//设置防御塔
void MyWindow::sett_tower(QPoint pressPos)
{
    Tower * tower=new Tower(pressPos,this,":/tower2.gif");//创建一个新的防御塔
    tower_list.push_back(tower);//把这个防御塔放到储存防御塔的list中
    update();//更新地图
    //qDebug()<<"防御塔";
}

//鼠标事件来操作创建防御塔显示
void MyWindow::mousePressEvent(QMouseEvent * event)
{
    QPoint pressPos=event->pos();//得到鼠标点击的位置
    Towerpos *it = nullptr;//防御塔坑容器中获取开始的位置 ----->注意定义指针必须要初始化为nullptr，不然导致成野指针后续程序出现异常崩溃
    for(int i=0;i<towerpos_list.count();i++)
    {
        it=towerpos_list.at(i);
        //如果是鼠标左键点击，若该塔坑存在防御塔，点击则升级，否则建立一座防御塔金币100
        if(Qt::LeftButton==event->button())
        {
            if(!it->iftower && it->ContainPos(pressPos) && (this->monoy>=100) )
            {
                qDebug()<<it->tow_pos.x()<<"   "<<it->tow_pos.y();
                this->monoy -= 100;
                Tower * tower=new Tower(pressPos,this,":/tower2.gif");
                tower_list.append(tower);
                it->iftower=true;
                it->settower(tower);
                update();//更新地图
                break;
            }
            if(it->iftower && it->ContainPos(pressPos) && (this->monoy>=100))//升级
            {
                if(it->get_tower()->towerrank<=3)
                {
                    it->get_tower()->towerrank++;
                    it->get_tower()->tower_Range += 20;
                    monoy -= 100;
                }
            }
        }
        //如果是鼠标右键点击,拆毁防御塔，返回金币一半
        else if(Qt::RightButton==event->button())
        {
            if(it->iftower && it->ContainPos(pressPos))
            {
                tower_list.removeOne(it->get_tower());
                it->get_tower()->deleteLater();
                it->iftower = false;
                monoy += 50;
            }

        }
    }

}
//添加防御塔坑
void MyWindow::addTowerpos()
{
    Towerpos *towerpos1 = new Towerpos(QPoint(345,85),":/open_spot.png");
    towerpos_list.push_back(towerpos1);//将所有的防御塔坑中心点的坐标存储在towerpos_listt容器中

    Towerpos *towerpos2 = new Towerpos(QPoint(345,215),":/open_spot.png");
    towerpos_list.push_back(towerpos2);

    Towerpos *towerpos3 = new Towerpos(QPoint(170,215),":/open_spot.png");
    towerpos_list.push_back(towerpos3);

    Towerpos *towerpos4 = new Towerpos(QPoint(170,370),":/open_spot.png");
    towerpos_list.push_back(towerpos4);

    Towerpos *towerpos5 = new Towerpos(QPoint(490,390),":/open_spot.png");
    towerpos_list.push_back(towerpos5);

    Towerpos *towerpos6 = new Towerpos(QPoint(350,390),":/open_spot.png");
    towerpos_list.push_back(towerpos6);

    Towerpos *towerpos7 = new Towerpos(QPoint(310,555),":/open_spot.png");
    towerpos_list.push_back(towerpos7);

}
//设置站点添加到站点列表中
void MyWindow::addwaytower()
{
    Waytower *waytower1 = new Waytower(QPoint(450,35));
    waytower_list.push_back(waytower1);

    Waytower *waytower2 = new Waytower(QPoint(450,145));
    waytower1->setnextwaypos(waytower2);//将第一个站点的下一个站点指针指向第二个站点
    waytower_list.push_back(waytower2);

    Waytower *waytower3 = new Waytower(QPoint(260,145));
    waytower2->setnextwaypos(waytower3);
    waytower_list.push_back(waytower3);

    Waytower *waytower4 = new Waytower(QPoint(260,320));
    waytower3->setnextwaypos(waytower4);
    waytower_list.push_back(waytower4);

    Waytower *waytower5 = new Waytower(QPoint(570,320));
    waytower4->setnextwaypos(waytower5);
    waytower_list.push_back(waytower5);

    Waytower *waytower6 = new Waytower(QPoint(570,490));
    waytower5->setnextwaypos(waytower6);
    waytower_list.push_back(waytower6);

    Waytower *waytower7 = new Waytower(QPoint(15,490));
    waytower6->setnextwaypos(waytower7);
    waytower_list.push_back(waytower7);

    waytower7->setnextwaypos(nullptr);//将最后一个站点的下一个站点指针指向空
}

//添加敌人
void MyWindow::addMyObject()
{  
    if(Curr_Count < Three_Count)
    {
        Waytower * startWayPoint;
        startWayPoint=waytower_list.first();//获取站点列表的第一个站点指针
        QString enemy_path;
        if(Curr_Level == First_Level)
        {
            enemy_path = ":/enemy1.gif";
        }
        if(Curr_Level == Second_Level)
        {
            enemy_path = ":/enemy2.gif";
        }
        if(Curr_Level == Three_Level)
        {
            enemy_path = ":/enemy3.gif";
        }
        Myobject * enemy=new Myobject(startWayPoint,enemy_path);//创建一个新得enemy
        enemy->currentHp += wavenum*20;//每增加一波，敌人的血量增加20
        enemy->maxHp += wavenum*20;
        myobject_list.push_back(enemy);
        //敌人到达基地发送信号
        connect(enemy,SIGNAL(Get_to_base_signals(Myobject*)),this,SLOT(enemy_Get_to_base(Myobject*)));
    }
}

//波数控制添加敌人
bool MyWindow::waveaddenemy()
{
    if(wavenum>=6)
    {
        return false;
    }
    else {
        QTimer::singleShot(10,this,&MyWindow::gameStart);
    }
    return true;
}
//控件的绘画
void MyWindow::controldraw()
{
    monoylabel->setText(QString(QStringLiteral("当前金币为：%1")).arg(this->monoy));//显示当前的金币
    base_Blood_label->setText(QString(QStringLiteral("当前基地血量：%1")).arg(this->base_Blood_volume));
    Curr_Level_label->setText(QString(QStringLiteral("当前关卡：%1")).arg(Curr_Level));
    Curr_Count_label->setText(QString(QStringLiteral("当前分数：%1")).arg(Curr_Count));
}

void MyWindow::updatescene()//定时器控制敌人移动
{
    foreach(Myobject* object,myobject_list)
    object->move();
    foreach(Tower * tower,tower_list)
    tower->checkEnemyInRange();
    update();
}

void MyWindow::gameStart()
{
    int enemyStartInterval[]={100,500,600,1000,3000,6000};//敌人出现的时间,控制敌人出场的时间，防止敌人重叠
    for(int i=0;i<6;++i)
    {
        QTimer::singleShot(enemyStartInterval[i],this,&MyWindow::addMyObject);//singleShot这个静态函数在一个给定时间间隔 msec(毫秒) 之后调用一个槽。
    }
}
//添加子弹
void MyWindow::addbullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    bullet_list.push_back(bullet);
    connect(bullet,SIGNAL(Bullet_Remove_signal(Bullet*)),this,SLOT(Bullet_Remove(Bullet*)));
    connect(bullet,SIGNAL(enemy_Blood_volume_signal(Myobject*)),this,SLOT(enemy_Blood_volume(Myobject*)));
}
//除去子弹
void MyWindow::removebullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    bullet_list.removeOne(bullet);
    bullet->deleteLater();
    bullet = nullptr;
    qDebug()<<QStringLiteral("子弹除去");
}
//敌人死亡，除去敌人
void MyWindow::removeenemy(Myobject *deadenemy,int enemy_dead_or_getbase)
{
    Q_ASSERT(deadenemy);
    //this->explode_list.removeOne(deadenemy->currentPos);
    this->myobject_list.removeOne(deadenemy);
    qDebug()<<QStringLiteral("敌人死亡")<<myobject_list.count();
    deadenemy->deleteLater();
    deadenemy = nullptr;
    if(this->myobject_list.empty())
    {
        if(waveaddenemy())//进行敌人添加的时候，同时判断波数是否达到
        {
            wavenum++;
        }
    }
    monoy+=50;
    if(enemy_dead_or_getbase == Game_enemy_dead)
    Curr_Count += 10;
    qDebug()<<QStringLiteral("清除成功");
}

MyWindow::~MyWindow()
{
    qDebug()<<"析构函数mywindow";
    this->deleteLater();
}
