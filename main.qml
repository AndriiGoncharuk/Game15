import QtQuick 2.0
import QtQuick.Controls 1.4

ApplicationWindow {
    id: applicationWindow
    visible: true
    title: qsTr("Game 15")
    width: 460; height: 300
    minimumWidth: sizeX * 35 + 160
    minimumHeight: sizeY * 35

    property int sizeX: 4
    property int sizeY: 4
    property alias textMoves: textMoves

    function showWin(titleText, messageText)
    {
        messageWindow.show();
        messageWindow.title = titleText;
        messageWindow.textID.text = messageText;
    }

    Image {
        id: background
        objectName: "BackgroundImage"
        width: parent.width; height: parent.height
        source: "qrc:/ResImg/background.png"

        Item {
            id: sidePanel
            width: 160
            anchors {right: parent.right; bottom: parent.bottom; top: parent.top}

            Column {
                id: panel
                anchors.fill: parent
                spacing: 10

                GroupBox {
                    id: setSize
                    width: 140; height: 20
                    anchors.horizontalCenter: parent.horizontalCenter

                    Rectangle {
                        id: edtSizeXback
                        width: 30; height: 22
                        color: "#66ffffff"; radius: 4
                        border {width: 1; color: "black"}
                        anchors {left: parent.left; leftMargin: 40; bottom: parent.bottom; bottomMargin: -15}

                        TextInput {
                            id: edtSizeX
                            anchors.fill: parent
                            text: qsTr("4")
                            horizontalAlignment: Text.AlignHCenter
                            font {family: "Arial"; bold: true; pixelSize: 20}
                            validator: RegExpValidator { regExp: /[1-9]\d?/ }
                        }
                    }

                    Rectangle {
                        id: edtSizeYback
                        width: 30; height: 22
                        color: "#66ffffff"; radius: 4
                        border {width: 1; color: "black"}
                        anchors {left: parent.left; leftMargin: 100; bottom: parent.bottom; bottomMargin: -15}

                        TextInput {
                            id: edtSizeY
                            anchors.fill: parent
                            text: qsTr("4")
                            horizontalAlignment: Text.AlignHCenter
                            font {family: "Arial"; bold: true; pixelSize: 20}
                            validator: RegExpValidator { regExp: /[1-9]\d?/ }
                        }
                    }

                    Text {
                        id: textX
                        text: qsTr("X")
                        anchors {left: parent.left; leftMargin: 80; bottom: parent.bottom; bottomMargin: -15}
                        font.pixelSize: 20
                    }

                    Text {
                        id: textSize
                        text: qsTr("Size:")
                        anchors {left: parent.left; leftMargin: -5; bottom: parent.bottom; bottomMargin: -15}
                        font.pixelSize: 20
                    }
                }

                Rectangle {
                    id: btnNew
                    width: 140; height: 25
                    color: "#fff888"; radius: 10.0
                    border {width: 1; color: "black"}
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        id: btnNewCaption
                        anchors.centerIn: parent
                        text: "Set size (new game)"
                        horizontalAlignment: Text.AlignHCenter
                        font {family: "Arial"; pixelSize: 15}
                    }

                    MouseArea {
                        id: mouseAreaNew
                        anchors.fill: parent

                        onClicked: { applicationWindow.showWin("are you sure", "Start new game?") }
                    }

                    states: State {
                            when: mouseAreaNew.pressed
                            PropertyChanges { target: btnNew; scale: 0.95; opacity: 0.80}
                    }
                }

                Rectangle {
                    id: btnRemix
                    width: 140; height: 25
                    color: "#90ff88"; radius: 10.0
                    border {width: 1; color: "black"}
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        id: btnRemixCaption
                        anchors.centerIn: parent
                        text: qsTr("Remix layout")
                        horizontalAlignment: Text.AlignHCenter
                        font {
                            family: "Arial"
                            pixelSize: 15
                        }
                    }

                    MouseArea {
                        id: mouseAreaRemix
                        anchors.fill: parent

                        onClicked: { applicationWindow.showWin("confirmation", "Remix layout?") }
                    }

                    states: State {
                            when: mouseAreaRemix.pressed
                            PropertyChanges { target: btnRemix; scale: 0.95; opacity: 0.80}
                    }
                }

                Rectangle {
                    id: btnClose
                    width: 140; height: 25
                    color: "#d78182"; radius: 10.0
                    border {width: 1; color: "black"}
                    anchors.horizontalCenter: parent.horizontalCenter

                    Text {
                        id: btnCloseCaption
                        anchors.centerIn: parent
                        text: qsTr("Close")
                        horizontalAlignment: Text.AlignHCenter
                        font {family: "Arial"; pixelSize: 15}
                    }

                    MouseArea {
                        id: mouseAreaClose
                        anchors.fill: parent

                        onClicked: { Qt.quit() }
                    }

                    states: State {
                            when: mouseAreaClose.pressed
                            PropertyChanges { target: btnClose; scale: 0.95; opacity: 0.80}
                    }
                }

                Text {
                    id: textMoves
                    width: 140; height: 28
                    text: qsTr("Moves: " + moves)
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 20

                    property int moves: 0
                }
            }
        }
        NumberAnimation { properties: "scale"; duration: 250; easing.type: Easing.InOutQuad }
    }

    GridView {
        id: areaGrid
        width: parent.width - 160
        height: parent.height
        anchors.top: parent.top
        anchors.left: parent.left
        cellWidth: (width - 1) / sizeX
        cellHeight: (height - 1) / sizeY
        enabled: false
        interactive: false
        focus: true;

        Rectangle {
            id: borderGridView
//            anchors.fill: parent
            width: parent.width - 1
            height: parent.height
            color: "#00000000"
            border.color: "black"
        }

        model: DataModel
        delegate: Tile {
            id: tileGridView
            width: areaGrid.cellWidth
            height: areaGrid.cellHeight
            objectName: model.value
            visible: (model.value !== sizeX * sizeY)

            MouseArea {
                id: tileMouseArea
                anchors.fill: parent
                onClicked: {
                    if (DataModel.onClick(model.index)) {
                        applicationWindow.showWin("Congratulations", "You win! Remix layout?")
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
