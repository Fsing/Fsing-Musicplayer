import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4

Item {
    property bool lineVisible: line.visible
    property string firstSource: firstButtonImage.source
    property string secondSource: secondButtonImage.source
    Button {
        id: firstButton
        MouseArea {
            id: firstButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
        }

        background: Image {
            id: firstButtonImage
            anchors.fill: parent
            opacity: 1
            source: "../images/leftArea/list.png"
        }
    }

    Button {
        id: secondButton
        anchors.left: firstButton.right
        anchors.leftMargin: 1
        anchors.bottom: firstButton.bottom

        MouseArea {
            id: secondButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
        }

        background: Image {
            id: secondButtonImage
            anchors.fill: parent
            opacity: 1
            source: "../images/leftArea/list.png"
        }
    }
}
