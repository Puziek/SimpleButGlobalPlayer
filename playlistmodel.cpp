#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent)
    : QAbstractListModel(parent)
{
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("C:/Users/kamil.puzio/Downloads/movie.wmv"));
    playlist->addMedia(QUrl("C:/Users/kamil.puzio/Downloads/rapapara.mp3"));
}

PlaylistModel::~PlaylistModel()
{
    delete playlist;
}

int PlaylistModel::rowCount(const QModelIndex& /*parent*/) const
{
    return playlist->mediaCount();
}

QVariant PlaylistModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= playlist->mediaCount()) {
        return QVariant();
    }

    const QMediaContent& media = playlist->media(index.row());

    if (role == Qt::DisplayRole) {
        return media.canonicalUrl().fileName();
    }

    return QVariant();
}

QMediaPlaylist* PlaylistModel::getPlaylist()
{
    return playlist;
}

void PlaylistModel::setPlayList(QMediaPlaylist* newPlaylist)
{
    beginResetModel();
    playlist = newPlaylist;
    endResetModel();
}
