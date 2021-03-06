import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.0
import "../dialog"

Rectangle {
    id: topArea
    width: parent.width
    height: 50
    color: "#C62F2F"
    radius: 0
    border.width: 0

    property var xPosition: 0.0
    property var yPosition: 0.0
    property alias loginDialog: loginDialog
    property alias topSearch: topSearch

    //--------------左上角图标
//    Image {
//        id: titleImage
//        x: 14
//        anchors.verticalCenter: parent.verticalCenter
//        source: "qrc:/images/topArea/title.png"
//    }
    Text {
        id: titleName
        x:14
        anchors.verticalCenter: parent.verticalCenter
        text: qsTr("FSing 音乐")
        font.pixelSize: 20
        color: "#CCCCCC"

    }
    //---------------前进后退按钮组件
    LeftRightButton {
        id: leftRightButton
        width: 52
        height: 21
        radius: 3
    }
    //----------------搜索组件
    TopSearch {
        id: topSearch
    }

    //-----------------右上角功能组件
    TopRightButton {
        id: topRightButton
        onLoginButtonClicked: {
            if (!client.logining) {
                loginDialog.open()
            } else {
                logoutDialog.y = topRightButton.height
                logoutDialog.x = (mainWindow.width - topRightButton.userx - logoutDialog.width / 2)
                if (logoutDialog.opened)
                    logoutDialog.close()
                else
                    logoutDialog.open()
            }
        }

        onUserImageClick: {
            console.log("onUserImageClicked")
            middleArea.personal.visible = true
            middleArea.allAttentions.visible = false
        }
    }
    LoginDialog {
        id: loginDialog
    }

    LogoutDialog {
        id: logoutDialog
    }

    //-----------------------------
    MouseArea {
        //top栏拖动
        x: 0 //parent.left
        width: 190
        height: parent.height
        hoverEnabled: false
        acceptedButtons: Qt.LeftButton
        property point clickPos: "0,0"
        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
            mainWindow.setX(mainWindow.x + delta.x)
            mainWindow.setY(mainWindow.y + delta.y)
            xPosition = mainWindow.x + delta.x
            yPosition = mainWindow.y + delta.y
        }
    }
    MouseArea {
        //搜索栏和设置按钮中间区域的拖动栏
        anchors.left: topSearch.right
        anchors.right: topRightButton.left
        height: parent.height
        hoverEnabled: false
        acceptedButtons: Qt.LeftButton
        property point clickPos: "0,0"
        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
            mainWindow.setX(mainWindow.x + delta.x)
            xPosition = mainWindow.x + delta.x
            mainWindow.setY(mainWindow.y + delta.y)
            yPosition = mainWindow.y + delta.y
        }
    }

    MouseArea {
        //top栏右侧 可拖动窗口大小
        width: 5
        height: parent.height
        x: parent.width - 5
        acceptedButtons: Qt.LeftButton
        property point clickPos: "0,0"
        onPressed: {
            clickPos = Qt.point(mouse.x, mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x - clickPos.x, mouse.y - clickPos.y)
            if (mainWindow.width + delta.x <= 1025) {

            } else {
                mainWindow.setWidth(mainWindow.width + delta.x)
            }
        }
    }
}
