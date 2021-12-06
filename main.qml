import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import GameEngine 1.0

ApplicationWindow {
    id: mainWindow

    width: 500
    height: 576
    visible: true
    title: "Reversi"
    contentItem.height: height - toolBar.height - footer.height
    color: "#E0E0E0"

    header: Options {
        id: toolBar
    }

    GameBoard {
          id: gameBoard

          anchors.centerIn: parent
    }

    footer: MessageArea {
        id: footer

        height: 32
    }

    GameEngine {
        id: engine

    }
}
