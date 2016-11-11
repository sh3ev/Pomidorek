#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    counter = 1500;
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this ,SLOT(myTimerHandler()));
    timer->start(1000);  // 100 nanoseconds or 1 second interval

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::myTimerHandler()
{
   counter--;
   int m = counter/60;
   int s = counter - (m*60);
   ui->label->setText(QString("%1:%2").arg(m).arg(s));

}
