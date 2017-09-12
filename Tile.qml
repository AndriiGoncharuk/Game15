import QtQuick 2.0
import QtQuick.Controls 1.4

Image {
        id: tile
        source: "qrc:/ResImg/tile.png"

        Rectangle {
            color: "#00000000"
            border.color: "#362e2e"
            anchors.fill: parent
        }

        Label {
            id: value
            text: parent.objectName
            font.family: "Times New Roman"
            font.bold: true
            font.pixelSize: ((parent.height > parent.width) ? parent.width : parent.height) - 15
            anchors.centerIn: parent
        }
}
