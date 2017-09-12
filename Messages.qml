import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2

Window {
//    id: messageWindow
    flags: Qt.WindowTitleHint

    property alias textID: textID

    signal signalDoIt

    width: 450; height: 100
    minimumWidth: width; minimumHeight: height
    maximumWidth: width; maximumHeight: height
    visible: false

    Button {
        width: 180; height: 50
        text: qsTr("OK")
        anchors {top: parent.top; topMargin: 40; left: parent.left; leftMargin: 10}
        onClicked: { messageWindow.signalDoIt() }
    }

    Button {
        width: 180; height: 50
        text: qsTr("cancel")
        anchors {top: parent.top; topMargin: 40; right: parent.right; rightMargin: 10}
        onClicked: { messageWindow.hide() }
    }

    Text {
        id: textID
        height: 25
        anchors {right: parent.right; left: parent.left; top: parent.top}
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 22
    }
}
