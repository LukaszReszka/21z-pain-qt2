import QtQuick 2.15
import QtQuick.Window 2.15


Rectangle {
    height: parent.height * 0.8
    width: height
    radius: parent.width
    color: engine.boardToShow[field.ind] === 'B'  ? "black" : "white"
    border.color: engine.boardToShow[field.ind] === 'W'  ? "black" : "white"
    border.width: 1
    visible: engine.boardToShow[field.ind] === '-'  ? false : true
}
