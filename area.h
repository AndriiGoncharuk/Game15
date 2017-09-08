#ifndef AREA_H
#define AREA_H
#include "tile.h"

const int AREASIZE = 4;

class Area : public QObject
{
    Q_OBJECT

public slots:
    void clickSlot(int x, int y);
    void remixSlot();

private:
    Tile *gameArea[AREASIZE][AREASIZE];
    uint8_t zeroX;
    uint8_t zeroY;
    QQmlApplicationEngine* engine;

    void mix();
    void show();
    void checkWin();

public:
    Area(QQmlApplicationEngine* engine);
    ~Area();
};

#endif // AREA_H
