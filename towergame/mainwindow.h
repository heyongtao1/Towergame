#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMediaPlayer>
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QPaintEvent>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
    QMediaPlayer *start_music;
    QMediaPlayer *battle_music;
};

#endif // MAINWINDOW_H
