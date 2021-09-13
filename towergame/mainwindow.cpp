#include <QDebug>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mybutton.h"
#include "mywindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(800,600);
    ui->setupUi(this);
    this->setWindowTitle(QString(QStringLiteral("屠杀恶魔城大战")));
    this->setWindowIcon(QIcon(QPixmap(":/enemy5.gif")));
    MyButton *start_Bt = new MyButton(":/start.jpg");
    start_Bt->setParent(this);
    start_Bt->move(350,250);

    //播放背景音乐
    start_music=new QMediaPlayer;
    start_music->setVolume(80);
    QMediaPlaylist *start_List = new QMediaPlaylist;//创建播放列表
    start_List->setPlaybackMode(QMediaPlaylist::Loop);
    start_List->addMedia(QUrl::fromLocalFile("D:\\Study\\Qt\\QTproject\\game-tower\\ceshi\\towergame\\background_music\\start_music.mp3"));
    start_music->setPlaylist(start_List);
    start_music->play();

    battle_music=new QMediaPlayer;
    QMediaPlaylist *gameList = new QMediaPlaylist;//创建播放列表
    gameList->setPlaybackMode(QMediaPlaylist::Loop);
    gameList->addMedia(QUrl::fromLocalFile("D:\\Study\\Qt\\QTproject\\game-tower\\ceshi\\towergame\\background_music\\battle.mp3"));
    gameList->addMedia(QUrl::fromLocalFile("D:\\Study\\Qt\\QTproject\\game-tower\\ceshi\\towergame\\background_music\\Second.mp3"));
    gameList->addMedia(QUrl::fromLocalFile("D:\\Study\\Qt\\QTproject\\game-tower\\ceshi\\towergame\\background_music\\Three.mp3"));
    battle_music->setPlaylist(gameList);
    battle_music->setVolume(80);

    MyWindow *scene = new MyWindow(battle_music);
    connect(start_Bt,&MyButton::clicked,this,[=](){
        start_Bt->zoomdown();
        start_Bt->zoomupt();
        QTimer::singleShot(600,this,[=](){
            this->hide();
            scene->show();
            start_music->stop();
            battle_music->play();
        });
    });

    connect(scene,&MyWindow::back_signals,this,[=](){    //将Mywindow的对象和主界面关联起来，Mywindow中的按钮发出clicked信号给Mywindow的对象，该对象发出back_signals信号给主界面
        scene->hide();
        this->show();
        battle_music->stop();
        start_music->play();
    });

}
//绘画函数
void MainWindow::paintEvent(QPaintEvent *)//运行主界面自动调用该函数
{
    QPainter painter(this);
    QPixmap pixmap(":/timg.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}
