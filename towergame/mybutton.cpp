
#include <QDebug>
#include <QPixmap>
#include <QPropertyAnimation>
#include "mybutton.h"

//在构造函数中设置按钮属性，比如大小、位置
MyButton::MyButton(QString pix):QPushButton(nullptr)//由于新建的自定义按钮类继承了QPushButton类,所以要初始化基类
{
   QPixmap pixmap(pix);//将图片路径传给QPixmap的对象
   this->setFixedSize(pixmap.width(),pixmap.height());//设置按钮大小
   this->setStyleSheet("QPushButton{border:Opx;}");//设置按钮根据图片的大小设置样式
   this->setIcon(pixmap);//设置图标
   this->setIconSize(QSize(pixmap.width(),pixmap.height()));//设置图标的大小
}
//按钮向下跳
void MyButton::zoomdown()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry"); //创建一个动态类的对象
    animation->setDuration(200);   //持续动态的时间
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));  //动态对象的开始位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height())); //动态对象的结束位置
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();  //动态效果开始
    //qDebug()<<"向下跳";
}
//按钮向上跳
void MyButton::zoomupt()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry"); //创建一个动态类的对象
    animation->setDuration(200);   //持续动态的时间
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));  //动态对象的开始位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height())); //动态对象的结束位置
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();  //动态效果开始
    //qDebug()<<"向上跳";
}
