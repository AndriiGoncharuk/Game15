import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Window {
    flags: Qt.WindowTitleHint
    id: messageWindow
    width: 450
    height: 100
    property alias textID: textID
    minimumWidth: width
    maximumWidth: width
    minimumHeight: height
    maximumHeight: height
    visible: false

    signal signalDoIt

    Button {
        x: 10
        y: textID.height + 15
        text: qsTr("OK")
        width: 180
        height: 50
        onClicked: { messageWindow.signalDoIt() }
    }

    Button {
        x: 260
        y: textID.height + 15
        text: qsTr("cancel")
        width: 180
        height: 50
        onClicked: { messageWindow.hide() }
    }

    Text {
        id: textID
        x: 0
        y: 0
        width: parent.width
        height: 25
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 22
    }
}
