#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void myTimerHandler();

private:
    Ui::MainWindow *ui;
    QTimer * timer;
    qint32  counter;
};

#endif // MAINWINDOW_H
