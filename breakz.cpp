#include "breakz.h"
#include "mainwindow.h"

#include <QDebug>

void Breakz::workTimerCall()
{
    qDebug () << "Work timer timeout";
    workTimer.stop();
    soundNotification->play();
    tray->startBlinking(500);
    connect(tray, &Tray::activated, this, &Breakz::stopWorkNotifications);
}

void Breakz::breakTimerCall()
{
    qDebug () << "Break timer timeout";
    breakTimer.stop();
    soundNotification->play();
    tray->startBlinking(500);
    connect(tray, &Tray::activated, this, &Breakz::stopBreakNotifications);
}

void Breakz::stopWorkNotifications()
{
    soundNotification->stop();
    disconnect(tray, &Tray::activated, this, &Breakz::stopWorkNotifications);
    tray->stopBlinking();
    tray->setBreakIcon();
    breakTimer.start();
}

void Breakz::stopBreakNotifications()
{
    soundNotification->stop();
    disconnect(tray, &Tray::activated, this, &Breakz::stopBreakNotifications);
    tray->stopBlinking();
    tray->setWorkIcon();
    workTimer.start();
}

Breakz::Breakz(MainWindow *parent)
    : QObject(parent)
    , mw(parent)
    , soundNotification(new Notification(this))
    , tray(new Tray(this))
    , updateTrayTimer(new QTimer(this))
{
    connect (tray, &Tray::activated, this, &Breakz::toggleMainWindow);
//    connect (tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(toggleMainWindow(QSystemTrayIcon::ActivationReason)));

   connect(&workTimer, &QTimer::timeout, this, QOverload<>::of(&Breakz::workTimerCall));
   connect(&breakTimer, &QTimer::timeout, this, QOverload<>::of(&Breakz::breakTimerCall));
   connect(&updateTrayTimer, &QTimer::timeout, this, QOverload<>::of(&Breakz::update));
   updateTrayTimer.setInterval(1000);
   updateTrayTimer.start();
}

void Breakz::setWorkTime(time_t t)
{
   workTime = t;
   workTimer.setInterval(t);
}

void Breakz::setBreakTime(time_t t)
{
    breakTime = t;
    breakTimer.setInterval(t);
}

void Breakz::start()
{
    tray->setWorkIcon();
    workTimer.start();
}

void Breakz::startFromBreak()
{
    tray->setBreakIcon();
    breakTimer.start();
}

void Breakz::stop()
{
    if (workTimer.isActive())
    workTimer.stop();
    if (breakTimer.isActive())
        breakTimer.stop();
}

void Breakz::update()
{
    QTime t(0, 0);
    if (workTimer.isActive())
        t = t.addMSecs(workTimer.remainingTime());
    else if (breakTimer.isActive())
        t = t.addMSecs(breakTimer.remainingTime());
    tray->setToolTip(t.toString());
}

void Breakz::toggleMainWindow(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Context)
    {
        qDebug () << "context requested";
        mw->setVisible(!mw->isVisible());
    }
}
