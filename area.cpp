#include <QQuickView>
#include <QTime>
#include "area.h"
#include "tile.h"

void Area::clickSlot(int x, int y)
{
    if ( (((zeroX == x-1)||(zeroX == x+1))&&(zeroY == y)) ||
         (((zeroY == y-1)||(zeroY == y+1))&&(zeroX == x)) ){
        gameArea[zeroX][zeroY] = gameArea[x][y];
        gameArea[zeroX][zeroY]->UpdatePos(zeroY, zeroX);
        zeroX = x; zeroY = y;
        gameArea[zeroX][zeroY] = nullptr;
        checkWin();
        QMetaObject::invokeMethod(engine->rootObjects().first()->findChild<QObject*>("ShowHide"), "moveInc");
    }
}

void Area::remixSlot()
{
    mix();
}

Area::Area(QQmlApplicationEngine* engine) : QObject(), engine(engine)
{
    for (int i = 0; i < AREASIZE; ++i) {
        for (int j = 0; j < AREASIZE; ++j) {
            if ((i+1 == AREASIZE) && (j+1 == AREASIZE)) {
                gameArea[i][j] = nullptr;
                zeroX = i;
                zeroY = j;
            }
            else {
                gameArea[i][j] = new Tile(i*AREASIZE + j + 1, AREASIZE, engine);
                QObject::connect(engine->findChild<QObject*>(QString::number(gameArea[i][j]->GetValue())),
                                 SIGNAL(mouseClick(int, int)), this, SLOT(clickSlot(int, int)));
            }
        }
    }
    QObject::connect(engine->rootObjects().first()->findChild<QObject*>("ShowHide"), SIGNAL(mixNow()), this, SLOT(remixSlot()));
    show();
}

Area::~Area()
{
    for (int i = 0; i < AREASIZE; ++i) {
        for (int j = 0; j < AREASIZE; ++j) {
            if (gameArea[i][j] != nullptr){
                delete gameArea[i][j];
            }
        }
    }
}

void Area::mix()
{
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    for (int i = 0; i < 10000; ++i) {
        if ((qrand() % 2) == 0) {
            if ((qrand() % 2) == 0) {
                if (zeroY > 0) {
                    gameArea[zeroX][zeroY] = gameArea[zeroX][zeroY-1];
                    gameArea[zeroX][zeroY-1] = nullptr;
                    zeroY--;
                }
            }
            else {
                if (zeroY < AREASIZE-1) {
                    gameArea[zeroX][zeroY] = gameArea[zeroX][zeroY+1];
                    gameArea[zeroX][zeroY+1] = nullptr;
                    zeroY++;
                }
            }

        }
        else {
            if ((qrand() % 2) == 0) {
                if (zeroX > 0) {
                    gameArea[zeroX][zeroY] = gameArea[zeroX-1][zeroY];
                    gameArea[zeroX-1][zeroY] = nullptr;
                    zeroX--;
                }
            }
            else {
                if (zeroX < AREASIZE-1) {
                    gameArea[zeroX][zeroY] = gameArea[zeroX+1][zeroY];
                    gameArea[zeroX+1][zeroY] = nullptr;
                    zeroX++;
                }
            }
        }
    }
    show();
}

void Area::show()
{
    for (int i = 0; i < AREASIZE; ++i) {
        for (int j = 0; j < AREASIZE; ++j) {
            if (gameArea[i][j] != nullptr) {
                gameArea[i][j]->UpdatePos(j, i);
            }
        }
    }
}

void Area::checkWin()
{
    bool isWin = true;
    for (int i = 0; i < AREASIZE; ++i) {
        for (int j = 0; j < AREASIZE; ++j) {
            if (gameArea[i][j] != nullptr) {
                if (!isWin) break;
                if (gameArea[i][j]->GetValue() != i*AREASIZE + j + 1) {
                    isWin = false;
                    break;
                }
            }
        }
    }
    if (isWin) {
        QMetaObject::invokeMethod(engine->rootObjects().first()->findChild<QObject*>("ShowHide"),
                                  "showWin", Q_ARG(QVariant, "Congratulations"), Q_ARG(QVariant, "You win! Remix layout?"));
    }
}
