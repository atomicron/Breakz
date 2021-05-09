#include "notification.h"

Notification::Notification(QObject *parent) : QObject(parent)
{
    alarmSound = ":/default_alarm.mp3";

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/default_alarm.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    sound = new QMediaPlayer;
    sound->setPlaylist(playlist);
}

void Notification::setSound(QString arg)
{
    alarmSound = arg;
}

void Notification::play()
{
    sound->play();
}

void Notification::stop()
{
    sound->stop();
}
