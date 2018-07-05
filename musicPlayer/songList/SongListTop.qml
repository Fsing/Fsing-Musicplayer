import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.2
import "./element"

Item {
    signal userClick
    signal collectClick
    signal shareClick
    signal downloadClick
    signal editClick

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
                    text: songlist.listname
                }
                Button {
                    id: editbutton
                    MouseArea {
                        id: editbuttonMouseArea
                        anchors.fill: parent
                        hoverEnabled: true
                        onClicked: editClick()
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

                Text {
                    text: songlist.username
                    MouseArea {
                        anchors.fill: parent
                        onClicked: userClick()
                    }
                }

                Text {
                    text: songlist.createTime
                }
            }

            RowLayout {
                spacing: 10
                PlayAllBtn {
                    id: addtoPlayListBtn
                }

                Button {
                    id: collectButton
                    text: "收藏"
                    onClicked: collectClick()
                }

                Button {
                    id: shareButton
                    text: "分享"
                    onClicked: shareClick()
                }

                Button {
                    id: downloadButton
                    text: "下载全部"
                    icon.source: "../images/leftArea/btndownload.png"
                    onClicked: downloadClick()
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
}
