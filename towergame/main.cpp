#include <QApplication>
#include "mainwindow.h"
#include "mdump.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    MiniDumper dump;
    w.show();

    return a.exec();
}
