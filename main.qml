import QtQuick 2.6
import QtQuick.Controls 1.4

ApplicationWindow {
    id: applicationWindow
    visible: true
    title: qsTr("Game 15")
    width: 0
    height: 0
    property alias textMoves: textMoves

    Image {
        id: background
        objectName: "BackgroundImage"
        width: parent.width
        height: parent.height
        source: "qrc:/ResImg/background.png"
    }

    Rectangle {
        width: parent.width-160
        height: parent.height
        color: "#00000000"
        border.color: "black"
    }

    Button {
        width: 140
        height: 50
        text: qsTr("Remix layout")
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10

        onClicked: { itemID.showWin("confirmation", "Remix layout?") }
    }

    Button {
        text: qsTr("Close")
        anchors.top: parent.top
        anchors.topMargin: 70
        anchors.right: parent.right
        anchors.rightMargin: 10
        width: 140
        height: 50

        onClicked: { Qt.quit() }
    }

    Text {
        property int moves: 0

        id: textMoves
        text: qsTr("Moves - " + moves)
        font.pointSize: 20
        anchors.top: parent.top
        anchors.topMargin: 120
        anchors.right: parent.right
        anchors.rightMargin: 10
        width: 140
        height: 50
    }

    Item {
        id: itemID
        objectName: "ShowHide"

        signal mixNow()

        function moveInc()
        {
            textMoves.moves++
            return null
        }

        function showWin(titleText, messageText)
        {
            messageWindow.show()
            messageWindow.title = titleText
            messageWindow.textID.text = messageText
            return null
        }
    }

    Messages {
            id: messageWindow
            objectName: "MessageWindow"
            modality: Qt.WindowModal
            visible: false

            onSignalRemix:
            {
                messageWindow.hide()
                textMoves.moves = 0;
                itemID.mixNow()
            }
    }
}
