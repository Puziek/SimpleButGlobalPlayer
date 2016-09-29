#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include "playlistmodel.h"
#include "playercontrols.h"

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QDateTime>

namespace Ui {
class MediaPlayer;
}

class MediaPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MediaPlayer(QWidget *parent = 0);
    ~MediaPlayer();

    void updatePositionInfo();

private:
    Ui::MediaPlayer *ui;
    QMediaPlayer* player;
    PlaylistModel* playlistModel;
    qint64 currMediaDuration;
};

#endif // MEDIAPLAYER_H
