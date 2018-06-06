import QtQuick 2.0

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
