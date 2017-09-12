#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <qqmlcontext.h>
#include "area.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Area data_model;

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QQmlContext *ctxt = view.rootContext();
    ctxt->setContextProperty("DataModel", &data_model);

    view.setSource(QUrl(QLatin1String("qrc:/main.qml")));
    QObject::connect(view.engine(), SIGNAL(quit()), QCoreApplication::instance(), SLOT(quit()));

    int res = app.exec();

//    delete data_model;

    return res;
}
