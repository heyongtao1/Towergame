#include "waytower.h"
#include "mywindow.h"

Waytower::Waytower(QPoint point):currpoint(point),
    nextwaypos(nullptr)
{

}

void Waytower::draw(QPainter *painter) const
{
    painter->save();//保存原始的绘画参数
    painter->setPen(Qt::green);//设置画笔的颜色
    painter->drawEllipse(currpoint,4,4);//画一个半径为4的圆
    //注意，图片的大小单位是像素
    painter->drawEllipse(currpoint,1,1);//半径为1的圆
    if(nextwaypos)//如果存在下一个航点，就把这两个航点连接起来
    {
        painter->drawLine(currpoint,nextwaypos->currpoint);//painter内的画直线的方法
    }
    painter->restore();//还原原来的画笔设置
}

//设置下一个站点的指针
void Waytower::setnextwaypos(Waytower *nextway)
{
    this->nextwaypos = nextway;
}

