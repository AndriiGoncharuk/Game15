#ifndef TILE_H
#define TILE_H
#include <stdint.h>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#define TILESIZE 75


class Tile : public QObject
{
protected:
    QQuickItem *m_TileQML;
public:
    Tile(uint8_t value, uint8_t areaSize, QQmlApplicationEngine* engine);
    uint8_t GetValue();
    void UpdatePos(uint8_t x, uint8_t y);
};

#endif // TILE_H
