#include "mediaplayer.h"
#include "ui_mediaplayer.h"

MediaPlayer::MediaPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MediaPlayer)
{
    ui->setupUi(this);
    playlistModel = new PlaylistModel();
    ui->lv_media->setModel(playlistModel);

    player = new QMediaPlayer;
    player->setPlaylist(playlistModel->getPlaylist());

    player->setVideoOutput(ui->vw_player);
    ui->vw_player->show();

    ui->pc_controlPanel->setState(player->state());
    ui->pc_controlPanel->setVolume(player->volume());
    ui->pc_controlPanel->setMuted(ui->pc_controlPanel->isMuted());
    ui->hs_position->setRange(0, player->duration() / 1000);

    connect(player, SIGNAL(volumeChanged(int)), ui->pc_controlPanel, SLOT(setVolume(int)));
    connect(player, SIGNAL(mutedChanged(bool)), ui->pc_controlPanel, SLOT(setMuted(bool)));
    connect(player, &QMediaPlayer::stateChanged, ui->pc_controlPanel, &PlayerControls::setState);

    connect(player, &QMediaPlayer::positionChanged, this, [this] (qint64 position) {
        if (!ui->hs_position->isSliderDown()) {
            ui->hs_position->setValue(position / 1000);
        }
        updatePositionInfo();
    });

    connect(player, &QMediaPlayer::durationChanged, this, [this] (qint64 duration) {
        qDebug() << "CHANGED" << duration / 1000;
        currMediaDuration = duration / 1000;
        ui->hs_position->setMaximum(duration / 1000);
    });

    connect(ui->pc_controlPanel, &PlayerControls::play, player, &QMediaPlayer::play);
    connect(ui->pc_controlPanel, &PlayerControls::stop, player, &QMediaPlayer::stop);
    connect(ui->pc_controlPanel, &PlayerControls::pause, player, &QMediaPlayer::pause);
    connect(ui->pc_controlPanel, &PlayerControls::next, player->playlist(), &QMediaPlaylist::next);
    connect(ui->pc_controlPanel, &PlayerControls::volumeChanged, player, &QMediaPlayer::setVolume);
    connect(ui->pc_controlPanel, &PlayerControls::muted, player, &QMediaPlayer::setMuted);

    /*connect(ui->hs_position, &QSlider::sliderMoved, this, [this] {
        qDebug() << ui->hs_position->value();
    });*/

    connect(ui->pc_controlPanel, &PlayerControls::previous, player, [this] {
        (player->position() >= 5000 || player->position() <= 1000) ? player->playlist()->previous() : player->setPosition(0);
    });

    connect(ui->hs_position, &QSlider::sliderMoved, this, [this] (int sec) {
        player->setPosition(sec * 1000);
    });

    ui->hs_position->setStyleSheet("QSlider::groove:horizontal {"
                                   "border: 1px solid #999999;"
                                   "height: 8px;"

                                   "border-radius: 3px;"
                                   "}"

                                   "QSlider::handle:horizontal {"
                                   "width: 8px;"
                                   "}"

                                   "QSlider::add-page:qlineargradient {"
                                   "background: lightgrey;"
                                   "border-top-right-radius: 3px;"
                                   "border-bottom-right-radius: 3px;"
                                   "border-top-left-radius: 0px;"
                                   "border-bottom-left-radius: 0px;"
                                   "}"

                                   "QSlider::sub-page:qlineargradient {"
                                   "background: #323B89;"
                                   "border-top-right-radius: 0px;"
                                   "border-bottom-right-radius: 0px;"
                                   "border-top-left-radius: 3px;"
                                   "border-bottom-left-radius: 3px;"
                                   "}");

}

MediaPlayer::~MediaPlayer()
{
    delete ui;
}

void MediaPlayer::updatePositionInfo()
{
    ui->l_mediaTime->setText(QString(QDateTime::fromTime_t(ui->hs_position->value()).toUTC().toString("hh:mm:ss") + "/" +
                                     QDateTime::fromTime_t(currMediaDuration).toUTC().toString("hh:mm:ss")));
}
