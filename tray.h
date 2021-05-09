#ifndef TRAY_H
#define TRAY_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QTimer>

class Tray : public QSystemTrayIcon
{
    Q_OBJECT

    QIcon workIcon;
    QIcon breakIcon;

    QTimer* blinkTimer;

    void blink();

    enum {
        iconBreak,
        iconWork
    } currentIcon;

public:
    explicit Tray(QObject *parent = nullptr);

    void setWorkIcon();
    void setBreakIcon();
    void setWorkIcon(QIcon);
    void setBreakIcon(QIcon);

    void startBlinking(time_t interval);
    void stopBlinking();

    void toggleIcon();


};

#endif // TRAY_H
