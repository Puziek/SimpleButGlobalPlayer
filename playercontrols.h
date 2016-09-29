#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <QWidget>
#include <QPushButton>
#include <QMediaPlayer>


namespace Ui {
class PlayerControls;
}

class PlayerControls : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerControls(QWidget *parent = 0);
    ~PlayerControls();

    QPushButton* playButton();
    QPushButton* stopButton();

    bool isMuted();
    QMediaPlayer::State getState();

public slots:
    void playClicked();
    void muteClicked();

    void setState(QMediaPlayer::State state);
    void setVolume(int volume);
    void setMuted(bool mute);

signals:
    void play();
    void pause();
    void stop();
    void next();
    void previous();
    void volumeChanged(int volume);
    void muted(bool isMuted);

private:
    QMediaPlayer::State playerState;
    Ui::PlayerControls *ui;
    bool isPlayerMuted;
};

#endif // PLAYERCONTROLS_H
