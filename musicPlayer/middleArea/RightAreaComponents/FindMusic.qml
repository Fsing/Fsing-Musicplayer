import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Layouts 1.2

Rectangle {
    property int index: 0
    property var interfaceParamter : client.getinterface()

    ColumnLayout{
        id: layout
        anchors.fill: parent
        spacing: 6
        RowLayout{

        Rectangle {
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.maximumHeight: 300
            Layout.maximumWidth: 300
            Layout.minimumHeight: 200
            SongListRectangle{
                playQuantity: String(50)
                source: "file:///"+applicationDirPath + "/" + interfaceParamter[6]
                songlistId: interfaceParamter[0]
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.maximumHeight: 300
            Layout.maximumWidth: 300
            Layout.minimumHeight: 200
            SongListRectangle{
                playQuantity: String(60)
                source: "file:///"+applicationDirPath + "/" + interfaceParamter[16]
                songlistId: interfaceParamter[10]
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.maximumHeight: 300
            Layout.maximumWidth: 300
            Layout.minimumHeight: 200
            SongListRectangle{
                playQuantity: String(70)
                source: "file:///"+applicationDirPath + "/" + interfaceParamter[26]
                songlistId: interfaceParamter[20]
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.maximumHeight: 300
            Layout.maximumWidth: 300
            Layout.minimumHeight: 200
            SongListRectangle{
                playQuantity: String(80)
                source: "file:///"+applicationDirPath + "/" + interfaceParamter[36]
                songlistId: interfaceParamter[30]
            }
        }
        }
        RowLayout{

        Rectangle {
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.maximumHeight: 300
            Layout.maximumWidth: 300
            Layout.minimumHeight: 200
            SongListRectangle{
                playQuantity: String(50)
                source: "file:///"+applicationDirPath + "/" + interfaceParamter[46]
                songlistId: interfaceParamter[40]
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.maximumHeight: 300
            Layout.maximumWidth: 300
            Layout.minimumHeight: 200
            SongListRectangle{
                playQuantity: String(60)
                source: "file:///"+applicationDirPath + "/" + interfaceParamter[56]
                songlistId: interfaceParamter[50]
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.maximumHeight: 300
            Layout.maximumWidth: 300
            Layout.minimumHeight: 200
            SongListRectangle{
                playQuantity: String(70)
                source: "file:///"+applicationDirPath + "/" + interfaceParamter[66]
                songlistId: interfaceParamter[60]
            }
        }
        Rectangle {
            Layout.fillWidth: true
            Layout.minimumWidth: 200
            Layout.maximumHeight: 300
            Layout.maximumWidth: 300
            Layout.minimumHeight: 200
            SongListRectangle{
                playQuantity: String(80)
                source: "file:///"+applicationDirPath + "/" + interfaceParamter[76]
                songlistId: interfaceParamter[70]
            }
        }
        }
    }

    /*
    ListModel {
        id:listmodel1
    }
                TableView {
                    id: tableview
                    anchors.fill: parent
                    model:listmodel1

                    TableViewColumn {
                        title: "音乐标题"
                        role: "title"
                    }
                    TableViewColumn {
                        title: "歌手"
                        role: "singer"
                    }

                    Component.onCompleted: {
                        listmodel1.append(
                                    {"title":songList[0],
                                            "singer":songList[1]}
                                        )
                        console.log(songList)
                    }


                }

/*
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
                currentPlaylist.addItem("rtsp://192.168.30.21/music/dukou.mp3")
                mediaPlayer.play()
                songChanged(currentPlaylist.currentItemSource)
                    dukou.add = true
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
                currentPlaylist.addItem("rtsp://192.168.30.21/music/zuimei.mp3")
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
                currentPlaylist.addItem("rtsp://192.168.30.21/music/yiluxiangbei.mp3")
                mediaPlayer.play()
                songChanged(currentPlaylist.currentItemSource)
                    yiluxiangbei.add = true
                }
            }
        }
    }
    */
}
