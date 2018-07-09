import QtQuick 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2

Item {
    property bool tvisible: false

    signal rightClick(var x, var y)

    Component {
        id: headView
        Item {
            width: parent.width
            height: 25

            ColumnLayout {
                RowLayout {
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                    spacing: 8
                    Text {
                        text: "id"
                        font.pixelSize: 15
                        Layout.preferredWidth: 120
                    }
                    Text {
                        text: "操作"
                        font.pixelSize: 15
                        Layout.preferredWidth: 120
                    }

                    Text {
                        text: "标题"
                        font.pixelSize: 15
                        Layout.preferredWidth: 120
                    }
                    Text {
                        text: "歌手"
                        font.pixelSize: 15
                        Layout.preferredWidth: 120
                    }
                    Text {
                        text: "专辑"
                        font.pixelSize: 15
                        Layout.preferredWidth: 120
                    }

                    Text {
                        text: "playQuantity"
                        font.pixelSize: 15
                        Layout.fillWidth: true
                    }
                }

                Rectangle {
                    id: horline
                    //模拟线段
                    width: rectangle.width //长
                    height: 1 //高
                    visible: true
                    color: "#d9d7d3" //颜色
                }
            }
        }
    } // headView is end

    Component {
        id: listRowItem

        Item {
            id: wrapper
            width: parent.width
            height: 25

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton

                onClicked: {

                    wrapper.ListView.view.currentIndex = index
                    if (mouse.button === Qt.RightButton) {
                        rightClick(mouseX, mouseY)
                    }
                }
                onDoubleClicked: {
                    propagateComposedEvents: true
                    client.songInformation(listmodel1.get(
                                               tableview.currentIndex).id)
                    if (!client.currentPlayListSong(
                                listmodel1.get(tableview.currentIndex).id)) {
                        mediaPlayer.playlist.addItem(
                                    listmodel1.get(
                                        tableview.currentIndex).source)
                        songChanged(listmodel1.get(
                                        tableview.currentIndex).source)
                        mediaPlayer.play()
                    }

                    mouse.accepted = false
                }
            }

            RowLayout {
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                spacing: 8

                Text {
                    text: id
                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
                    font.pixelSize: wrapper.ListView.isCurrentItem ? 15 : 14
                    Layout.preferredWidth: 120
                }

                TwoButton {
                    id: button_2
                    z: 3
                    anchors.top: parent.top
                    anchors.topMargin: -3
                    Layout.preferredWidth: 120
                    onButtonClick: {
                        wrapper.ListView.view.currentIndex = index
                    }
                }
                Text {
                    text: name
                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
                    elide: Text.ElideRight
                    font.pixelSize: wrapper.ListView.isCurrentItem ? 15 : 14
                    Layout.preferredWidth: 120
                }
                Text {
                    text: singer
                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
                    elide: Text.ElideRight
                    font.pixelSize: wrapper.ListView.isCurrentItem ? 15 : 14
                    Layout.preferredWidth: 120
                }
                Text {
                    text: album
                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
                    elide: Text.ElideRight
                    font.pixelSize: wrapper.ListView.isCurrentItem ? 15 : 14
                    Layout.preferredWidth: 120
                }

                Text {
                    text: playQuantity
                    color: wrapper.ListView.isCurrentItem ? "red" : "black"
                    font.pixelSize: wrapper.ListView.isCurrentItem ? 15 : 14
                    Layout.fillWidth: true
                }
            }
        }
    }

    ListView {
        id: tableview
        anchors.fill: parent
        delegate: listRowItem
        model: songlist.model
        header: headView
        focus: true
        currentIndex: -1

        highlight: Rectangle {
            color: "lightblue"
        }
    }
    onTvisibleChanged: {
        if (!tvisible)
            tableview.visible = false
        else {
            tableview.visible = true
        }
    }

    onRightClick: {
        songOperationDialog.x = x
        songOperationDialog.y = topArea.height + songListTop.height + 40
                + rec.height + 10 + 25 * tableview.currentIndex + y
        console.log("songlistcurrentindex:   " + tableview.currentIndex)
        console.log(songOperationDialog.x + "," + songOperationDialog.y)
        if (songOperationDialog.opened) {
            songOperationDialog.close()
        } else {
            songOperationDialog.open()
            songOperationDialog.clickSongIndex(tableview.currentIndex)
        }
    }
}
