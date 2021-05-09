#ifndef BREAKZ_H
#define BREAKZ_H

#include "tray.h"
#include "notification.h"

#include <QObject>
#include <QTimer>
#include <QTime>

class MainWindow;

class Breakz : public QObject
{
    Q_OBJECT

    MainWindow* mw;

    Notification* soundNotification;
    Tray* tray;

    using time_t = unsigned int;

    time_t workTime;
    time_t breakTime;

    QTimer workTimer;
    QTimer breakTimer;


    void workTimerCall();
    void breakTimerCall();
    void stopBreakNotifications();
    void stopWorkNotifications();

    QTimer updateTrayTimer;

public:
    explicit Breakz(MainWindow *parent = nullptr);

    void setWorkTime(time_t);
    void setBreakTime(time_t);
    void start();
    void startFromBreak();
    void stop();

    const time_t DEFAULT_WORK_INTERVAL = 5*1000;
    const time_t DEFAULT_BREAK_INTERVAL = 5*1000;
//    const time_t DEFAULT_WORK_INTERVAL = 45*60*1000;
//    const time_t DEFAULT_BREAK_INTERVAL = 15*60*1000;
    void update();

public slots:
    void toggleMainWindow(QSystemTrayIcon::ActivationReason);

signals:

};

#endif // BREAKZ_H
