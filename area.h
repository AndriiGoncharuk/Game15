#ifndef AREA_H
#define AREA_H
#include <QAbstractListModel>
#include "tile.h"

class Area : public QAbstractListModel{
    Q_OBJECT
//    Q_PROPERTY(int clickInd READ getClickInd WRITE setClickInd)

public:
    enum TileValues {
        TileValue = Qt::UserRole + 1,
    };

    Area(QObject *parent = 0);
    void addTile(const Tile &tile);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    Q_INVOKABLE void newSize(int newX, int newY);
    Q_INVOKABLE bool onClick(int tileIndex);
    Q_INVOKABLE void mix();
    ~Area();

private:
    QList<Tile> m_tiles;

    void moveTile(int tileIndexFrom, int tileIndexTo, int8_t delta);
    bool checkWin();

protected:
    uint8_t sizeX;
    uint8_t sizeY;
    int zeroT;
//    int _clickInd;
//    int getClickInd() const;
//    void setClickInd(int val);

    void fillArea();
    QHash<int, QByteArray> roleNames() const;
};

#endif // AREA_H
