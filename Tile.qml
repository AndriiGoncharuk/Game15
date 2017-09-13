import QtQuick 2.0
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0

Image {
    id: tile
    source: "qrc:/ResImg/tile.png"
    layer.enabled: true
    layer.effect: OpacityMask {
        maskSource: Item {
            width: tile.width
            height: tile.height
            Rectangle { anchors.fill: parent; radius: ( (height > width) ? width : height ) / 10 }
        }
    }

    Rectangle {
        id: borderTile
        anchors.fill: parent
        color: "#00000000"
        radius: ( (height > width) ? width : height ) / 10
        border.color: "#362e2e"
    }

    Label {
        id: value
        anchors.centerIn: parent
        text: parent.objectName
        font {family: "Times New Roman"; bold: true;
                pixelSize: ((parent.height > parent.width) ? parent.width : parent.height) - 15}
    }
}
