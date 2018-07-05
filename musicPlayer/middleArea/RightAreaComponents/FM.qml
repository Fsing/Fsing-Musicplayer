import QtQuick 2.0
import "../../songList"

Rectangle {
    property int index: 1
    color: "yellow"

    //    Text {
    //        anchors.centerIn: parent
    //        text: qsTr("FM")
    //    }
    SongList {
        id: songlist
        width: parent.width
        height: parent.height
        ListModel {
            id: listmodel
            ListElement {
                number: "01"
                title: "稻香"
                singer: "周杰伦"
                songlist: "稻香"
                time: "03:48"
            }
            ListElement {
                number: "01"
                title: "稻香"
                singer: "周杰伦"
                songlist: "稻香"
                time: "03:48"
            }
            ListElement {
                number: "01"
                title: "稻香"
                singer: "周杰伦"
                songlist: "稻香"
                time: "03:48"
            }
            ListElement {
                number: "01"
                title: "稻香"
                singer: "周杰伦"
                songlist: "稻香"
                time: "03:48"
            }
            ListElement {
                number: "01"
                title: "稻香"
                singer: "周杰伦"
                songlist: "稻香"
                time: "03:48"
            }
        }
        model: listmodel
        listname: "zzzz"
        listImg: "qrc:/images/logo.jpg"
        userImg: "qrc:/images/logo.jpg"
        username: "zhy"
        createTime: "2018-09-01"
    }
}
