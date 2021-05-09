#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , breakz(new Breakz(this))
{
    ui->setupUi(this);

    connect (ui->timeEdit, SIGNAL(timeChanged(const QTime&)), this, SLOT(timeChangedWork(const QTime&)));
    connect (ui->timeEdit_2, SIGNAL(timeChanged(const QTime&)), this, SLOT(timeChangedBreak(const QTime&)));

    connect (ui->btn_start, SIGNAL(clicked(bool)), this, SLOT(startPressed()));
    connect (ui->btn_startFromBreak, SIGNAL(clicked(bool)), this, SLOT(startFromBreakPressed()));
    connect (ui->btn_quit, SIGNAL(clicked(bool)), this, SLOT(quitPressed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug () << "Custom close event";
    setVisible(false);
    event->ignore();
}

void MainWindow::timeChangedWork(const QTime& time)
{
    breakz->setWorkTime((time.minute() * 60 + time.second()) * 1000);
}

void MainWindow::timeChangedBreak(const QTime &time)
{
    breakz->setBreakTime((time.minute() * 60 + time.second()) * 1000);
}

void MainWindow::startPressed()
{
    breakz->stop();
    breakz->setWorkTime((ui->timeEdit->time().minute() * 60 + ui->timeEdit->time().second()) * 1000);
    breakz->setBreakTime((ui->timeEdit_2->time().minute() * 60 + ui->timeEdit_2->time().second()) * 1000);
    breakz->start();
}

void MainWindow::startFromBreakPressed()
{
    breakz->stop();
    breakz->setWorkTime((ui->timeEdit->time().minute() * 60 + ui->timeEdit->time().second()) * 1000);
    breakz->setBreakTime((ui->timeEdit_2->time().minute() * 60 + ui->timeEdit_2->time().second()) * 1000);
    breakz->startFromBreak();
}

void MainWindow::quitPressed()
{
    QApplication::exit(0);
}

