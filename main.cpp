#include "mainwindow.h"
#include <QApplication>
#include <QtMultimedia/QSound>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    QSound::play(":/new/sounds/sounds/work_sound.wav");


    return a.exec();
}
