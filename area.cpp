#include <QQuickView>
#include <QTime>
#include "area.h"
#include "tile.h"
#include <QDebug>

Area::Area(QObject *parent) : QAbstractListModel(parent) {
    sizeX = 4;
    sizeY = 4;
    zeroT = sizeX*sizeY-1;
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    fillArea();
    endInsertRows();
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

//int Area::getClickInd() const {
//    return _clickInd;
//}

//void Area::setClickInd(int val) {
//    beginMoveRows(QModelIndex(),val,val,QModelIndex(),val-1);
//    m_tiles.swap(val, val-1);
//    endMoveRows();
//    _clickInd = val;
//}

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
    if (tileIndex-zeroT == 1) {moveTile(tileIndex, zeroT, 1);};
    if (tileIndex-zeroT == -1) {moveTile(zeroT, tileIndex, -1);};
    if (tileIndex-zeroT == sizeX) {moveTile(tileIndex, zeroT, sizeX);};
    if (tileIndex-zeroT == -sizeX) {moveTile(zeroT, tileIndex, -sizeX);};
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
        if ((qrand() % 2) == 0)
        {
            if ((qrand() % 2) == 0)
            {
                if (zeroT % sizeX > 0)
                {
//                    beginMoveRows(QModelIndex(),zeroT,zeroT,QModelIndex(),zeroT-1);
//                    m_tiles.swap(zeroT, zeroT-1);
//                    zeroT--;
//                    endMoveRows();
                    qDebug() << zeroT << "left";
                    moveTile(zeroT, zeroT-1,-1);
                }
            }
            else
            {
                if (zeroT % sizeX < sizeX-1)
                {
//                    beginMoveRows(QModelIndex(),zeroT+1,zeroT+1,QModelIndex(),zeroT);
//                    m_tiles.swap(zeroT, zeroT+1);
//                    zeroT++;
//                    endMoveRows();
                    qDebug() << zeroT << "right";
                    moveTile(zeroT+1, zeroT,+1);
                }
            }
        }
        else
        {
            if ((qrand() % 2) == 0)
            {
                if (zeroT / sizeX > 0)
                {
//                    beginMoveRows(QModelIndex(),zeroT-sizeX,zeroT-sizeX,QModelIndex(),zeroT);
//                    endMoveRows();
//                    beginMoveRows(QModelIndex(),zeroT,zeroT,QModelIndex(),zeroT-sizeX);
//                    m_tiles.swap(zeroT, zeroT-sizeX);
//                    zeroT -= sizeX;
//                    endMoveRows();
                    qDebug() << zeroT << "up";
                    moveTile(zeroT, zeroT-sizeX,-sizeX);
                }
            }
            else
            {
                if (zeroT / sizeX < sizeY-1)
                {
//                    beginMoveRows(QModelIndex(),zeroT,zeroT,QModelIndex(),zeroT+sizeX);
//                    endMoveRows();
//                    beginMoveRows(QModelIndex(),zeroT+sizeX,zeroT+sizeX,QModelIndex(),zeroT);
//                    m_tiles.swap(zeroT, zeroT+sizeX);
//                    zeroT += sizeX;
//                    endMoveRows();
                    qDebug() << zeroT << "down";
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
