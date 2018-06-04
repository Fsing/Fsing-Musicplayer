import QtQuick 2.0

Rectangle {
    y:topArea.height
    height: parent.height - topArea.height -bottomArea.height
    width: parent.width
    color: "white"
}
