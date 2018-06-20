import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4

Rectangle {
    property int index: 0
    color: "white"


    Rectangle {
        id:dukou
        width: parent.width
        height: 30
        Text {
            text: qsTr("dukou")
        }
        MouseArea {
            anchors.fill: parent
            onClicked:selectSong("rtsp://192.168.30.21/music/dukou.mp3")
        }
    }
    Rectangle {
        id:zuimei
        width: parent.width
        height: 30
        anchors.top: dukou.bottom
        Text {
            text: qsTr("zuimei")
        }
        MouseArea {
            anchors.fill: parent
            onClicked:selectSong("rtsp://192.168.30.21/music/zuimei.mp3")
        }
    }
    Rectangle {
        width: parent.width
        height: 30
        anchors.top: zuimei.bottom
        Text {
            text: qsTr("yiluxiangbei")
        }
        MouseArea {
            anchors.fill: parent
            onClicked:selectSong("rtsp://192.168.30.21/music/yiluxiangbei.mp3")
        }
    }
}
