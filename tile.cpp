#include <QQuickWindow>
#include <stdint.h>
#include "tile.h"

Tile::Tile(uint8_t value, uint8_t areaSize, QQmlApplicationEngine* engine) : QObject()
{
    if (engine != NULL)
    {
        QQuickWindow *window = qobject_cast<QQuickWindow*>(engine->rootObjects().at(0));
        if (!window)
        {
            qFatal("Error: Your root item has to be a window.");
        }
        QQuickItem *root = window->contentItem();
        QQmlComponent component(engine, QUrl("qrc:/Tile.qml"));
        m_TileQML = qobject_cast<QQuickItem*>(component.create());
        QQmlEngine::setObjectOwnership(m_TileQML, QQmlEngine::CppOwnership);
        m_TileQML->setParentItem(root);
        m_TileQML->setParent(engine);
        m_TileQML->setProperty("visible", true);
        m_TileQML->setProperty("size", areaSize);
        m_TileQML->setProperty("width", TILESIZE);
        m_TileQML->setProperty("height", TILESIZE);
        m_TileQML->setProperty("objectName", value);
    }
}

void Tile::UpdatePos(uint8_t x, uint8_t y)
{
    m_TileQML->setProperty("cellX", x);
    m_TileQML->setProperty("cellY", y);
}

uint8_t Tile::GetValue()
{
    return m_TileQML->property("objectName").toInt();
}
