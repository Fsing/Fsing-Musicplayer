import QtQuick 2.0
import QtQuick.Controls 1.4

Rectangle {
    anchors.top: topArea.bottom
    anchors.bottom: bottomArea.top
    anchors.left: parent.left
    anchors.right: parent.right
    color: "white"

    LeftArea {
        id: leftArea
    }
    RightArea {
        id: rightArea
    }

}
