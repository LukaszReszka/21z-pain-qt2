import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Text {
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    style: Text.Outline;
    styleColor: "#006633"
    color: "#00CC66"
    font.pixelSize: footer.height*0.6
    text: engine.message
}
