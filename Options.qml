import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ToolBar {
    RowLayout {

        ToolButton {
            text: "&Nowa Gra"
            onClicked: engine.resetGame()
        }

        ToolButton {
            text: "&Pomoc"
            onClicked: Qt.openUrlExternally("https://www.kurnik.pl/reversi/zasady.phtml")
        }

        ToolButton {
            text: "&Wyjście"
            onClicked: mainWindow.close()
        }
    }

}
