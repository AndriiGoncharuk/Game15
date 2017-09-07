import QtQuick 2.6
import Qt.labs.controls 1.0

ApplicationWindow {
    visible: true
    title: qsTr("Game 15")

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
        x: parent.width-width-10
        y: 15
        text: qsTr("Remix layout")
        width: 140
        height: 50

        onClicked: { itemID.showWin("confirmation", "Remix layout?") }
    }

    Button {
        x: parent.width-width-10
        y: 15 + 50 + 15
        text: qsTr("Close")
        width: 140
        height: 50

        onClicked: { Qt.quit() }
    }

    Item {
        id: itemID
        objectName: "ShowHide"

        signal mixNow()

        function hideWin()
        {
            messageWindow.hide()
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
                itemID.mixNow()
            }
    }
}
