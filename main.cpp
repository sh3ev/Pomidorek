#include "mainwindow.h"
#include <QApplication>
#include <QtMultimedia/QSound>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    QSound::play(":/new/sounds/sounds/work_sound.wav");
    w.showNotification("WORK", "Let's do something !");

    return a.exec();
}
