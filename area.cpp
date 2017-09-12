#include <QQuickView>
#include <QTime>
#include "area.h"
#include "tile.h"

Area::Area(QObject *parent) : QAbstractListModel(parent) {
    newSize(4, 4);
}

void Area::addTile(const Tile &tile) {
    m_tiles.append(tile);
}

int Area::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return m_tiles.count();
}

QVariant Area::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_tiles.count())
        return QVariant();

    const Tile &tile = m_tiles[index.row()];
    if (role == TileValue)
        return tile.getvalue();

    return QVariant();
}

void Area::fillArea() {
    for (int i = 0; i <= zeroT; ++i)
    {
        addTile(i+1);
    }
}

void Area::newSize(int newX, int newY) {
    beginResetModel();
    m_tiles.clear();
    sizeX = newX;
    sizeY = newY;
    zeroT = sizeX*sizeY-1;
    fillArea();
    endResetModel();
}

bool Area::onClick(int tileIndex) {
    if (tileIndex-zeroT == 1) {
        moveTile(tileIndex, zeroT, 1);
    }
    if (tileIndex-zeroT == -1) {
        moveTile(zeroT, tileIndex, -1);
    }
    if (tileIndex-zeroT == sizeX) {
        moveTile(tileIndex, zeroT, sizeX);
    }
    if (tileIndex-zeroT == -sizeX) {
        moveTile(zeroT, tileIndex, -sizeX);
    }
    return checkWin();
}

void Area::moveTile(int tileIndexFrom, int tileIndexTo, int8_t delta) {
    if (tileIndexFrom - tileIndexTo > 1) {
        beginMoveRows(QModelIndex(),tileIndexTo,tileIndexTo,QModelIndex(),tileIndexFrom);
        endMoveRows();
    }
    beginMoveRows(QModelIndex(),tileIndexFrom,tileIndexFrom,QModelIndex(),tileIndexTo);
    m_tiles.swap(tileIndexFrom, tileIndexTo);
    zeroT+=delta;
    endMoveRows();
}

void Area::mix() {
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    for (int i = 0; i < 10000; ++i) {
        if ((qrand() % 2) == 0) {
            if ((qrand() % 2) == 0) {
                if (zeroT % sizeX > 0) {
                    moveTile(zeroT, zeroT-1,-1);
                }
            }
            else {
                if (zeroT % sizeX < sizeX-1) {
                    moveTile(zeroT+1, zeroT,+1);
                }
            }
        }
        else {
            if ((qrand() % 2) == 0) {
                if (zeroT / sizeX > 0) {
                    moveTile(zeroT, zeroT-sizeX,-sizeX);
                }
            }
            else {
                if (zeroT / sizeX < sizeY-1) {
                    moveTile(zeroT+sizeX, zeroT,+sizeX);
                }
            }
        }
    }
}

Area::~Area() {
    m_tiles.clear();
}

bool Area::checkWin() {
    bool isWin = true;
    for (int var = 0; var < m_tiles.length(); ++var) {
            if (var+1 != m_tiles[var].getvalue()) {
                isWin = false;
                break;
            };
        }
    return isWin;
}

QHash<int, QByteArray> Area::roleNames() const {
    QHash<int, QByteArray> values;
    values[TileValue] = "value";
    return values;
}
