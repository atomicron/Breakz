#include "tray.h"

void Tray::blink()
{
    toggleIcon();
}

Tray::Tray(QObject *parent)
    : QSystemTrayIcon(parent)
    , blinkTimer(new QTimer(this))
{
    connect (blinkTimer, &QTimer::timeout, this, QOverload<>::of(&Tray::blink));

    QPixmap green(100,100);
    green.fill(QColor("green"));
    QPixmap red(100,100);
    red.fill(QColor("red"));

    workIcon = QIcon(green);
    breakIcon = QIcon(red);

    setIcon(workIcon);
    currentIcon = iconWork;
    show();
}

void Tray::setWorkIcon()
{
    setIcon(workIcon);
}

void Tray::setBreakIcon()
{
    setIcon(breakIcon);
}

void Tray::setWorkIcon(QIcon icon)
{
    workIcon = icon;
}

void Tray::setBreakIcon(QIcon icon)
{
    breakIcon = icon;
}

void Tray::startBlinking(time_t interval)
{
    blinkTimer->setInterval(interval);
    blinkTimer->start();
}

void Tray::stopBlinking()
{
    blinkTimer->stop();
}

void Tray::toggleIcon()
{
    if (currentIcon == iconWork) {
        currentIcon = iconBreak;
        setIcon(breakIcon);
    }
    else {
        setIcon(workIcon);
        currentIcon = iconWork;
    }
}
