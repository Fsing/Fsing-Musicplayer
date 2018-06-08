import QtQuick 2.0


Rectangle {
    color: "white"
    Item {
        id: header
        width: parent.width
        height: parent.height * 0.8
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        Image {
            id: close
            width: 20
            height: 20
            source: "../images/leftArea/close.png"
            anchors{
                right: parent.right
                rightMargin: 10
                top:parent.top
                topMargin: 10

            }
            MouseArea {
                anchors.fill: close
                focus: true
                acceptedButtons: Qt.LeftButton
                onClicked: {
                    loginDialog.close()
                }
            }
        }

        MyButton {
            id: login
            width: parent.width * 0.7
            height: 50
            radius: 20
            anchors {
                left: header.left
                leftMargin: parent.width * 0.3 / 2.0
                top: parent.top
                topMargin: 50
            }
            text: "手机号登录"
        }
        MyButton {
            id: register
            width: parent.width * 0.7
            height: 50
            radius: 20
            anchors {
                top: login.bottom
                topMargin: 20
                left: header.left
                leftMargin: parent.width * 0.3 / 2.0
            }
            text: "手机号登录"
        }

        MouseArea {
            anchors {
                left: parent.left
                bottom: parent.bottom
                top: parent.top
                right: parent.right
                rightMargin: 20
            }

            hoverEnabled: false
            acceptedButtons: Qt.LeftButton
            property point clickpos: "0,0"
            onPressed: {
                clickpos = Qt.point(mouse.x, mouse.y)
            }
            onPositionChanged: {
                var delta = Qt.point(mouse.x - clickpos.x, mouse.y - clickpos.y)
                loginDialog.x = (loginDialog.x + delta.x)
                loginDialog.y = (loginDialog.y + delta.y)
            }
        }
    }
    Item {
        id: bottomitem
        width: parent.width
        height: parent.height * 0.2
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        ImageButton {
            id: weixin
            width: 50
            height: 60
            radius: 20
            anchors {
                left: parent.left
                leftMargin: 50
                top: parent.top
                topMargin: 10
            }
            source: "../images/cloudMusic.ico"
            text: "微信"
        }
        ImageButton {
            width: 50
            height: 60
            radius: 20
            anchors {
                left: weixin.right
                leftMargin: 20
                top: parent.top
                topMargin: 10
            }
            text: "QQ"
            source: "../images/cloudMusic.ico"
        }
    }
}
