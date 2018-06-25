import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4

Rectangle {
    property int index: 0
    color: "white"


    Rectangle {
        property bool add: false
        id:dukou
        width: parent.width
        height: 30
        Text {
            text: qsTr("dukou")
        }
        MouseArea {
            anchors.fill: parent
            onClicked:{
                if(!dukou.add){
                currentPlaylist.addItem("rtsp://192.168.43.164/music/dukou.mp3")
                mediaPlayer.play()
                songChanged(currentPlaylist.currentItemSource)
                    dukou.add = true
                    console.log(dukou.add)
                }
            }
        }
    }
    Rectangle {
        property bool add: false
        id:zuimei
        width: parent.width
        height: 30
        anchors.top: dukou.bottom
        Text {
            text: qsTr("zuimei")
        }
        MouseArea {
            anchors.fill: parent
            onClicked:{
                if(!zuimei.add){
                currentPlaylist.addItem("rtsp://192.168.43.164/music/zuimei.mp3")
                mediaPlayer.play()
                songChanged(currentPlaylist.currentItemSource)
                    zuimei.add =true
                }
            }
        }
    }
    Rectangle {
        id:yiluxiangbei
        property bool add: false
        width: parent.width
        height: 30
        anchors.top: zuimei.bottom
        Text {
            text: qsTr("yiluxiangbei")
        }
        MouseArea {
            anchors.fill: parent
            onClicked:{
                if(!yiluxiangbei.add){
                currentPlaylist.addItem("rtsp://192.168.43.164/music/yiluxiangbei.mp3")
                mediaPlayer.play()
                songChanged(currentPlaylist.currentItemSource)
                    yiluxiangbei.add = true
                }
            }
        }
    }
}
