import QtQuick 2.0
import Qt.labs.controls 1.0

    Image {
        id: tile
        property int cellX: 0
        property int cellY: 0
        property int size: 1
        width: ((parent == null) ? 0 : (parent.width - 160)/size)
        height: ((parent == null) ? 0 : parent.height/size)
        x: cellX*width
        y: cellY*height
        source: "qrc:/ResImg/tile.png"

        signal mouseClick(int x, int y)

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
            font.pixelSize: ((parent.height > parent.width) ? parent.width : parent.height) - 2
            anchors.centerIn: parent
        }

        Behavior on x { PropertyAnimation { easing.overshoot: 2; easing.type: Easing.InOutBack; duration: 500} }
        Behavior on y { PropertyAnimation { easing.overshoot: 2; easing.type: Easing.InOutBack; duration: 500} }

        MouseArea {
               anchors.fill: parent
               onClicked: { mouseClick(parent.cellY, parent.cellX) }
        }
}
