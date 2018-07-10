import QtQuick 2.0

Rectangle {
    property int index: 5
    color:"green"
    Rectangle {
        property bool add: false
        id:dukou
        width: parent.width
        height: 30
        Text {
            text: qsTr("clicked me to download")
        }
        MouseArea {
            anchors.fill: parent
            onClicked:{
                client.fileTransfer("zaiaiwoyici.jpg")

            }
        }
    }
}
