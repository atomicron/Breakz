#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QObject>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Notification : public QObject
{
    Q_OBJECT
    QMediaPlayer* sound;
    QString alarmSound;

public:
    explicit Notification(QObject *parent = nullptr);

    void setSound(QString);
    void play();
    void stop();

signals:

};

#endif // NOTIFICATION_H
