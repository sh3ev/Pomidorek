#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    work_time = 16;
    sb_time = 6;
    lb_time = 11;
    count = 0;

    work_timer = new QTimer(this);
    sb_timer = new QTimer(this);
    lb_timer = new QTimer(this);

    connect(work_timer,SIGNAL(timeout()), this ,SLOT(WorkTimerHandler()));
    connect(sb_timer,SIGNAL(timeout()), this ,SLOT(SmallBreakTimerHandler()));
    connect(lb_timer,SIGNAL(timeout()), this ,SLOT(LongBreakTimerHandler()));
    work_timer->start(1000);  // 100 nanoseconds or 1 second interval

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::WorkTimerHandler()
{

      if(work_time >= 1 && count <= 4)
      {
          work_time--;
          int m = work_time/60;
          int s = work_time - (m*60);
          ui->label->setText(QString("%1:%2").arg(m).arg(s));

      }

      else if (work_time < 1 && count < 3)
      {

          work_timer->stop();
          count++;
          work_time = 16;
          sb_timer->start(1000);
      }
      else
      {

          work_timer->stop();
          lb_timer->start(1000);
      }

}

void MainWindow::SmallBreakTimerHandler()
{
    if(sb_time >= 1)
    {
        sb_time--;
        int m = sb_time/60;
        int s = sb_time - (m*60);
        ui->label->setText(QString("%1:%2").arg(m).arg(s));
    }
    else
    {
        sb_timer->stop();
        sb_time = 6;
        work_timer->start(1000);
    }


}

void MainWindow::LongBreakTimerHandler()
{
    if(lb_time >= 1)
    {
        lb_time--;
        int m = lb_time/60;
        int s = lb_time - (m*60);
        ui->label->setText(QString("%1:%2").arg(m).arg(s));
    }
    else
    {
        lb_timer->stop();
        lb_time = 11;
        count = 0;
        work_time = 16;
        work_timer->start(1000);
    }
}
