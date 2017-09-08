#ifndef TILE_H
#define TILE_H
#include <stdint.h>
#include <QQmlApplicationEngine>
#include <QQuickItem>

const int TILESIZE = 75;

class Tile : public QObject
{

private:
    QQuickItem *m_TileQML;

public:
    Tile(uint8_t value, uint8_t areaSize, QQmlApplicationEngine* engine);
    void UpdatePos(uint8_t x, uint8_t y);
    uint8_t GetValue();
    ~Tile();
};

#endif // TILE_H
