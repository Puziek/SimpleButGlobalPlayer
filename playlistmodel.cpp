#include "playlistmodel.h"

PlaylistModel::PlaylistModel(QObject *parent)
    : QAbstractListModel(parent)
{
    playlist = new QMediaPlaylist();
    setPlayList(playlist);
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
    disconnect(playlist, &QMediaPlaylist::mediaAboutToBeInserted, this, &PlaylistModel::beginInsertItems);
    disconnect(playlist, &QMediaPlaylist::mediaInserted, this, &PlaylistModel::endInsertItems);
    disconnect(playlist, &QMediaPlaylist::mediaAboutToBeRemoved, this, &PlaylistModel::beginRemoveItems);
    disconnect(playlist, &QMediaPlaylist::mediaRemoved, this, &PlaylistModel::endRemoveItems);

    beginResetModel();
    playlist = newPlaylist;

    connect(playlist, &QMediaPlaylist::mediaAboutToBeInserted, this, &PlaylistModel::beginInsertItems);
    connect(playlist, &QMediaPlaylist::mediaInserted, this, &PlaylistModel::endInsertItems);
    connect(playlist, &QMediaPlaylist::mediaAboutToBeRemoved, this, &PlaylistModel::beginRemoveItems);
    connect(playlist, &QMediaPlaylist::mediaRemoved, this, &PlaylistModel::endRemoveItems);

    endResetModel();
}

void PlaylistModel::beginInsertItems(int start, int end)
{
    beginInsertRows(QModelIndex(), start, end);
}

void PlaylistModel::endInsertItems()
{
    endInsertRows();
}

void PlaylistModel::beginRemoveItems(int start, int end)
{
    beginRemoveRows(QModelIndex(), start, end);
}

void PlaylistModel::endRemoveItems()
{
    endRemoveRows();
}
