#include "playercontrols.h"
#include "ui_playercontrols.h"

PlayerControls::PlayerControls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerControls)
{
    ui->setupUi(this);
    playerState = QMediaPlayer::StoppedState;
    isPlayerMuted = false;

    ui->pb_previous->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->pb_next->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->pb_stop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pb_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pb_mute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    connect(ui->pb_play, &QPushButton::clicked, this, &PlayerControls::playClicked);
    connect(ui->pb_mute, &QPushButton::clicked, this, &PlayerControls::muteClicked);
    connect(ui->pb_next, &QPushButton::clicked, this, &PlayerControls::next);
    connect(ui->pb_previous, &QPushButton::clicked, this, &PlayerControls::previous);
    connect(ui->pb_stop, &QPushButton::clicked, this, &PlayerControls::stop);
    connect(ui->hs_volume, &QSlider::valueChanged, this, &PlayerControls::volumeChanged);
}

PlayerControls::~PlayerControls()
{
    delete ui;
}

QPushButton *PlayerControls::playButton()
{
    return ui->pb_play;
}

QPushButton *PlayerControls::stopButton()
{
    return ui->pb_stop;
}

void PlayerControls::setState(QMediaPlayer::State state)
{
    if (state != playerState) {
        playerState = state;

        switch (state) {
        case QMediaPlayer::StoppedState:
            ui->pb_stop->setEnabled(false);
            ui->pb_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        case QMediaPlayer::PlayingState:
            ui->pb_stop->setEnabled(true);
            ui->pb_play->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        case QMediaPlayer::PausedState:
            ui->pb_stop->setEnabled(true);
            ui->pb_play->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        }
    }
}

void PlayerControls::setVolume(int volume)
{
    ui->hs_volume->setValue(volume);
}

void PlayerControls::setMuted(bool mute)
{
    if (mute != isPlayerMuted) {
        isPlayerMuted = mute;

        ui->pb_mute->setIcon(style()->standardIcon(mute
                    ? QStyle::SP_MediaVolumeMuted
                    : QStyle::SP_MediaVolume));
    }
}

bool PlayerControls::isMuted()
{
    return isPlayerMuted;
}

QMediaPlayer::State PlayerControls::getState()
{
    return playerState;
}

void PlayerControls::playClicked()
{
    switch (playerState) {
    case QMediaPlayer::StoppedState:
    case QMediaPlayer::PausedState:
        emit play();
        break;
    case QMediaPlayer::PlayingState:
        emit pause();
        break;
    }
}

void PlayerControls::muteClicked()
{
    emit muted(!isPlayerMuted);
}
