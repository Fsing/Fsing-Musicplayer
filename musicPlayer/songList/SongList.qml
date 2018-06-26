import QtQuick 2.0
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.4

Rectangle {
    id: songlist
    property int index: 10
    color: "green"

    ColumnLayout {
        spacing: 60
        RowLayout {
            spacing: 30
            RecIcon {
                id: icon
            }
            ColumnLayout {
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

        ColumnLayout {
            Row {
                id: rec
                spacing: 10
                Button {
                    text: "歌曲列表"
                }
                Button {
                    text: "评论"
                }
                Button {
                    text: "收藏者"
                }
            }
            Rectangle {
                id: horline
                anchors.top: rec.bottom
                //模拟线段
                width: songlist.width //长
                height: 1 //高
                visible: true
                color: "#7c7171" //颜色
            }
        }
    }
}
