#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>
#include <QtMultimedia/QSound>
#include <QCloseEvent>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tomato_1->setEnabled(false);
    ui->tomato_2->setEnabled(false);
    ui->tomato_3->setEnabled(false);
    ui->tomato_4->setEnabled(false);





    if(QSystemTrayIcon::isSystemTrayAvailable())
    {

        // tray settings
        trayIcon = new QSystemTrayIcon(this);
        trayIconMenu = new QMenu(this);
        // setting actions
        QAction *QAquit=new QAction("&Quit",this);
        QAction *QAshow=new QAction("&Show",this);

        //adding actions to context menu
        trayIconMenu->addAction(QAquit);
        trayIconMenu->addAction(QAshow);
        trayIcon->setContextMenu(trayIconMenu);

        // tray ico set
        trayIcon->setIcon(this->windowIcon());
        trayIcon->show();


        work_time = 16;
        sb_time = 6;
        lb_time = 11;
        count = 0;

        work_timer = new QTimer(this);
        sb_timer = new QTimer(this);
        lb_timer = new QTimer(this);





        //setup ui slots
        connect(QAquit,SIGNAL(triggered()),qApp,SLOT(quit()));
        connect(QAshow,SIGNAL(triggered()),this,SLOT(show()));
//                connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
//                this,SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
//        connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(show()));
        connect(work_timer,SIGNAL(timeout()), this, SLOT(WorkTimerHandler()));
        connect(sb_timer,SIGNAL(timeout()), this ,SLOT(SmallBreakTimerHandler()));
        connect(lb_timer,SIGNAL(timeout()), this ,SLOT(LongBreakTimerHandler()));
        work_timer->start(1000);  // 100 nanoseconds or 1 second interval
    }else{
        //Error out and quit
        QMessageBox::critical(this,"Abort","Unsupported Desktop Environment.  Exiting");
        exit(EXIT_FAILURE);
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent * event)
{
    event->ignore();
    this->hide();
}



void MainWindow::showNotification(QString title, QString message)
{
    trayIcon->showMessage(title, message);
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::DoubleClick:
        this->show();
        break;
    case QSystemTrayIcon::MiddleClick:
        this->showMinimized();
        break;
    default:
        ;

    }
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
          QSound::play(":/new/sounds/sounds/break_sound.wav");
          trayIcon->showMessage("SHORT BREAK","It's time for short break !");
          work_timer->stop();
          count++;
          work_time = 16;
          sb_timer->start(1000);
      }
      else
      {
          QSound::play(":/new/sounds/sounds/applause.wav");
          trayIcon->showMessage("LONG BREAK","It's time for long break !");
          work_timer->stop();
          lb_timer->start(1000);
      }

      if(count == 1)
      {
          //ui->label->setText("SHORT BREAK");
          ui->tomato_1->setEnabled(true);
      }
      if(count == 2)
      {
          //ui->label->setText("SHORT BREAK");
          ui->tomato_2->setEnabled(true);
      }
      if(count == 3) ui->tomato_3->setEnabled(true);
      if(count == 4) ui->tomato_4->setEnabled(true);

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
        QSound::play(":/new/sounds/sounds/work_sound.wav");
        trayIcon->showMessage("WORK","Let's do something !");
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

        ui->tomato_1->setEnabled(false);
        ui->tomato_2->setEnabled(false);
        ui->tomato_3->setEnabled(false);
        ui->tomato_4->setEnabled(false);
        QSound::play(":/new/sounds/sounds/work_sound.wav");
        work_timer->start(1000);
    }
}
