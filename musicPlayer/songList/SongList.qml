import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "./element"

Rectangle {
    id: songlist
    property int index: 9

    ScrollView {
        id: scroll
        anchors.fill: parent

        clip: true
        style: ScrollViewStyle {
            id: ss
            transientScrollBars: true
        }
        horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        //        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
        ColumnLayout {
            y: 20
            spacing: 40
            SongListTop {
                id: songListTop
                width: songlist.width
                height: (songlist.height - 60) / 2
            }

            SongListBottom {
                id: songListBottom
                width: songlist.width
                //                height: 25*
            }
        }
    }
}
