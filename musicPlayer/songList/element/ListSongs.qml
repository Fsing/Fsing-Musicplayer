import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

Item {
    property bool tvisible: false
    property int row: listmodel.count
    ListModel {
        id: listmodel
        ListElement {
            number: "01"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
        ListElement {
            number: "02"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
        ListElement {
            number: "03"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
        ListElement {
            number: "04"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
        ListElement {
            number: "05"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
        ListElement {
            number: "06"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
        ListElement {
            number: "07"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
        ListElement {
            number: "08"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
        ListElement {
            number: "09"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
        ListElement {
            number: "10"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
        ListElement {
            number: "11"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
        ListElement {
            number: "12"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
        ListElement {
            number: "13"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
        ListElement {
            number: "14"
            title: "一路向北"
            singer: "周杰伦"
            songlist: "zjl"
            time: "03:48"
        }
    }

    TableView {
        id: tableview
        visible: false
        anchors.fill: parent
        model: listmodel
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        frameVisible: false //隐藏表格最外面的矩形框线
        rowDelegate: Rectangle {
            height: 25
            color: styleData.selected ? "#d1cccc" : (styleData.alternate ? "#f7f6f6" : "white")
        }

        headerDelegate: Rectangle {
            id: rec
            height: 25
            //                    color: "white"
            border.width: 1
            border.color: "#f7f6f6"
            Text {
                //                anchors.centerIn: parent
                anchors.verticalCenter: parent.verticalCenter
                text: styleData.value
            }
        }

        TableViewColumn {
            title: "  "
            role: "number"
        }

        TableViewColumn {
            title: "音乐标题"
            role: "title"
        }

        TableViewColumn {
            title: "歌手"
            role: "singer"
        }

        TableViewColumn {
            title: "专辑"
            role: "songlist"
        }

        TableViewColumn {
            title: "时长"
            role: "time"
        }
    }
    onTvisibleChanged: {
        if (!tvisible)
            tableview.visible = false
        else {
            tableview.visible = true
        }
    }
}
