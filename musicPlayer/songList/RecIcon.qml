import QtQuick 2.0

Rectangle {
    property string source: icon.source
    width: 250
    height: 250
    border.width: 1
    signal clicked

    Image {
        id: icon
        source: ""
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            clicked()
        }
    }
}
