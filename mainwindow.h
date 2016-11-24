#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QtMultimedia/QSound>
#include <QCloseEvent>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showNotification(QString title, QString message);

private slots:
    void WorkTimerHandler();
    void SmallBreakTimerHandler();
    void LongBreakTimerHandler();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void showMessage();
    void messageClicked();
    void closeEvent(QCloseEvent*);

private:
    Ui::MainWindow *ui;
    QTimer * work_timer;
    QTimer * sb_timer;
    QTimer * lb_timer;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;


    QAction *QAquit;       //quit application

    qint32  work_time;
    qint32 sb_time; //small break time
    qint32 lb_time; //long break time
    qint32 count;



};

#endif // MAINWINDOW_H
