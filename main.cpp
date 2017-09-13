#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <qqmlcontext.h>
#include "area.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Area data_model;

    engine.rootContext()->setContextProperty("DataModel", &data_model);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
