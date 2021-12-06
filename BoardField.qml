import QtQuick 2.15
import QtQuick.Window 2.15

Rectangle {
    id: field

    readonly property int column: index % 8
    readonly property int row: Math.floor(index/8)
    readonly property int ind: index
    width: gameBoard.width/8
    height: width
    color: (column + row) % 2 == 0 ? "#006633" : "#00CC66"

    Pawn {
        anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: engine.processPlayersMove(parent.column, parent.row)
    }
}
