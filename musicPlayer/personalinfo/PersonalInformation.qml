import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1

Rectangle{
    id:personalInformation
    width: parent.width
    height: parent.height
    //    width: 700
    //    height: 500

    property string createdSongListNumber: "0"
    property string collectedSongListNumber: "1"

    ScrollView {
        id: leftItem
        anchors.fill: parent
        clip: true
        style: ScrollViewStyle {
            id: ss
            transientScrollBars: true
        }
        ColumnLayout{
//            x:40
//            y:20
            anchors{
                top:parent.top
                topMargin: 20
                left: parent.left
                leftMargin: 40
            }
            spacing: 20
            UserBaseInfo{
                id:userBaseInfo
                width: personalInformation.width - 40
                height: personalInformation.height * 0.4
            }

            //分割线
            Rectangle{
                id:fengexian1
                width: personalInformation.width + 10
                height: 30
                border.width: 1
                border.color: "#dcdcdc"
                Text {
                    text: qsTr("创建的歌单( " + createdSongListNumber+" )")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                }
            }
            PersonalCreatedSongLists{
                id:personalCreatedSongLists
                width: personalInformation.width
                height:500
            }
            //分割线
            Rectangle{
                id:fengexian2
                width: personalInformation.width + 10
                height: 30
                border.width: 1
                border.color: "#dcdcdc"
                Text {
                    text: qsTr("收藏的歌单( " + collectedSongListNumber+" )")
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                }
            }
            PersonalCollectedSongLists{
                id:personalCollectedSongLists
                width: personalInformation.width
                height:500
            }
        }
    }
}
