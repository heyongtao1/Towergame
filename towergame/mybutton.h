#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QPushButton>//实现按钮动态弹跳的头文件

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    MyButton(QString pix);
    void zoomdown();//按钮向下跳
    void zoomupt();//按钮向上跳
signals:

public slots:
};

#endif // MYBUTTON_H
