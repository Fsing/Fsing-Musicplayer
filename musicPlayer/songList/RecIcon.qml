import QtQuick 2.0

Rectangle {
    property string source: icon.source
    width: 200
    height: 200
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
