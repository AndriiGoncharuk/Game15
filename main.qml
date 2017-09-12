import QtQuick 2.0
import QtQuick.Controls 1.4

ApplicationWindow {
    id: applicationWindow
    visible: true
    title: qsTr("Game 15")
    width: 460
    height: 300
    minimumWidth: sizeX*35+160
    minimumHeight: sizeY*35
    property int sizeX: 4
    property int sizeY: 4
    property alias textMoves: textMoves

    Image {
        id: background
        objectName: "BackgroundImage"
        width: parent.width
        height: parent.height
        source: "qrc:/ResImg/background.png"

        function showWin(titleText, messageText)
        {
            messageWindow.show()
            messageWindow.title = titleText
            messageWindow.textID.text = messageText
            return null
        }

        Text {
            text: qsTr("Size:")
            anchors.right: parent.right
            anchors.rightMargin: 107
            anchors.top: parent.top
            anchors.topMargin: 0
            font.pixelSize: 20
        }

        Text {
            text: qsTr("X")
            anchors.right: parent.right
            anchors.rightMargin: 50
            anchors.top: parent.top
            anchors.topMargin: 0
            font.pixelSize: 20
        }

        TextInput {
            id: edtSizeX
            width: 30
            height: 20
            text: qsTr("4")
            horizontalAlignment: Text.AlignHCenter
            anchors.right: parent.right
            anchors.rightMargin: 70
            anchors.top: parent.top
            anchors.topMargin: 3
            font.pixelSize: 20
            validator: RegExpValidator { regExp: /[1-9]\d?/ }
        }

        TextInput {
            id: edtSizeY
            width: 30
            height: 20
            text: qsTr("4")
            horizontalAlignment: Text.AlignHCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 3
            font.pixelSize: 20
            validator: RegExpValidator { regExp: /[1-9]\d?/ }
        }

        Button {
            width: 140
            height: 25
            text: "Set size (new game)"
            anchors.top: parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 10

            onClicked: { background.showWin("are you sure", "Start new game?") }
        }

        Button {
            width: 140
            height: 25
            text: qsTr("Remix layout")
            anchors.top: parent.top
            anchors.topMargin: 55
            anchors.right: parent.right
            anchors.rightMargin: 10

            onClicked: { background.showWin("confirmation", "Remix layout?") }
        }

        Button {
            width: 140
            height: 25
            text: qsTr("Close")
            anchors.top: parent.top
            anchors.topMargin: 85
            anchors.right: parent.right
            anchors.rightMargin: 10

            onClicked: { Qt.quit() }
        }


        Text {
            property int moves: 0
            id: textMoves
            text: qsTr("Moves: " + moves)
            font.pointSize: 20
            anchors.top: parent.top
            anchors.topMargin: 110
            anchors.right: parent.right
            anchors.rightMargin: 10
            width: 140
            height: 28
        }
    }

    GridView {
        id: areaGrid
        width: parent.width-160
        height: parent.height
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        cellWidth: width / sizeX
        cellHeight: height / sizeY
        enabled: false
        interactive: false
        focus: true;

        Rectangle {
            anchors.fill: parent
            color: "#00000000"
            border.color: "black"
        }

        model: DataModel
        delegate: Tile {
            width: areaGrid.cellWidth//-5
            height: areaGrid.cellHeight//-5
            objectName: model.value
            visible: (model.value !== sizeX*sizeY)

            MouseArea {
                anchors.fill: parent
                onClicked: {
//                        DataModel.clickInd = model.index
                        if (DataModel.onClick(model.index)) {
                            background.showWin("Congratulations", "You win! Remix layout?")
                        }
                        textMoves.moves++
                }
            }
        }
        move: Transition {
            NumberAnimation {
                properties: "x,y"
                easing.overshoot: 2
                easing.type: Easing.InOutBack
                duration: 500
            }
        }
        moveDisplaced: move
    }

    Messages {
        id: messageWindow
        objectName: "MessageWindow"
        modality: Qt.WindowModal
        visible: false

        onSignalDoIt: {
            messageWindow.hide()
            textMoves.moves = 0
            if (messageWindow.title != "are you sure") {
                DataModel.mix()
                areaGrid.enabled = true
            }
            else {
                sizeX = edtSizeX.text
                sizeY = edtSizeY.text
                DataModel.newSize(sizeX, sizeY)
                areaGrid.enabled = false
            }
        }
    }
}
