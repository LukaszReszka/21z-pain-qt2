import QtQuick 2.15
import QtQuick.Window 2.15

Grid {
    id: gameBoard

    columns: 8
    width: height
    height : 512
    scale: mainWindow.width <= mainWindow.contentItem.height ?
               mainWindow.width/width : mainWindow.contentItem.height/height

    Repeater {
        model: 64
        BoardField {
        }
    }
}
