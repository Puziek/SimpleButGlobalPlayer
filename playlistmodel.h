#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include <QAbstractListModel>
#include <QMediaPlaylist>

class PlaylistModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit PlaylistModel(QObject *parent = 0);
    ~PlaylistModel();

    int rowCount(const QModelIndex& parent = {}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QMediaPlaylist* getPlaylist();
    void setPlayList(QMediaPlaylist* newPlaylist);


private:
    QMediaPlaylist* playlist;
};

#endif // PLAYLISTMODEL_H
