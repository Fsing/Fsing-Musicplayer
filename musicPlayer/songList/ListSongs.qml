import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

Item {
    property bool tvisible: false
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
    }

    TableView {
        id: tableview
        visible: false
        anchors.fill: parent
        model: listmodel

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
