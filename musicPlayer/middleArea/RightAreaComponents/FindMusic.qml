import QtQuick 2.0

Rectangle {
    property int index: 0
    color: "blue"
    Text {
        anchors.centerIn: parent
        text: qsTr("发现音乐")
    }
}
