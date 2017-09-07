#ifndef AREA_H
#define AREA_H
#include "tile.h"
#define AREASIZE 4

class Area : public QObject
{
    Q_OBJECT
protected:
    Tile *gameArea[AREASIZE][AREASIZE];
    uint8_t zeroX;
    uint8_t zeroY;
public slots:
    void ClickSlot(int x, int y);
    void RemixSlot();
public:
    Area(QQmlApplicationEngine* engine);
    void Mix();
    void Show();
    void CheckWin();
    QQmlApplicationEngine* engine;
};

#endif // AREA_H
