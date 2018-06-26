import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.4

Rectangle {
    id: songlist
    property int index: 10
    color: "green"
    ScrollView {
        id: scroll
        anchors.fill: parent
        Column {
            id: layout
            y: 50
            spacing: 60
            RowLayout {
                x: 50
                spacing: 30
                RecIcon {
                    id: icon
                }
                ColumnLayout {
                    spacing: 15
                    RowLayout {

                        Label {
                            text: "歌单"
                        }
                        Text {
                            text: "歌单名"
                        }
                        Button {
                            id: editbutton
                            MouseArea {
                                id: editbuttonMouseArea
                                anchors.fill: parent
                                hoverEnabled: true
                            }

                            background: Image {
                                id: editbuttonImage
                                anchors.fill: parent
                                opacity: 1
                                source: "../images/leftArea/list.png"
                            }
                        }
                    }

                    RowLayout {
                        CircleIcon {
                        }

                        Button {
                            text: "用户名"
                        }

                        Text {
                            text: "创建时间"
                        }
                    }

                    RowLayout {
                        PlayAllBtn {
                            id: addtoPlayListBtn
                        }

                        Button {
                            id: collectButton
                            anchors.left: addtoPlayListBtn.right
                            anchors.leftMargin: 10
                            text: "收藏"
                        }

                        Button {
                            id: shareButton
                            anchors.left: collectButton.right
                            anchors.leftMargin: 10
                            text: "分享"
                        }

                        Button {
                            id: downloadButton
                            anchors.left: shareButton.right
                            anchors.leftMargin: 10
                            text: "下载全部"
                            icon.source: "../images/leftArea/btndownload.png"
                        }
                    }

                    RowLayout {
                        Label {
                            text: "标签"
                        }
                        Button {
                            text: "添加标签"
                        }
                    }

                    RowLayout {
                        Label {
                            text: "简介"
                        }
                        Button {
                            text: "添加简介"
                        }
                    }
                }
            }

            Column {
                RowLayout {
                    id: rec
                    x: 50
                    spacing: 10
                    Button {
                        text: "歌曲列表"
                        onClicked: {
                            listsongs.tvisible = true
                        }
                    }
                    Button {
                        text: "评论"
                        onClicked: {
                            listsongs.tvisible = false
                        }
                    }
                    Button {
                        text: "收藏者"
                        onClicked: {
                            listsongs.tvisible = false
                        }
                    }
                }
                Rectangle {
                    id: horline
                    anchors.top: layout.bottom
                    //模拟线段
                    width: songlist.width //长
                    height: 2 //高
                    visible: true
                    color: "black" //颜色
                }
                Rectangle {
                    border.width: 1
                    width: songlist.width
                    height: songlist.height - icon.height - 50 - rec.height
                    ListSongs {
                        id: listsongs
                        anchors.fill: parent
                    }
                }
            }
        }
    }
}
