#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include "area.h"
#include "tile.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    QObject *rootObject = engine.rootObjects().first();
    rootObject->setProperty("width", AREASIZE * TILESIZE + 160);
    rootObject->setProperty("height", AREASIZE * TILESIZE);
    rootObject->setProperty("minimumWidth", AREASIZE * TILESIZE/2 + 160);
    rootObject->setProperty("minimumHeight", AREASIZE * TILESIZE/2);

    Area *gameArea = new Area(&engine);

    int res = app.exec();

    delete gameArea;

    return res;
}
