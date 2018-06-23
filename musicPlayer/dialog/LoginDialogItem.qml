import QtQuick 2.0
import "common"

Rectangle {
    color: "white"

    signal userLoginClicked   //账户登录按钮
    signal userRegisterClicked  //用户注册按钮
    signal returnClicked    //返回按钮
    signal loginClicked     //输入信息后，确认登录按钮
    signal registerClicked  //输入信息后，确认注册按钮

    property alias middleItemVisibe:middleItem.visible
    property alias middleLoginItemVisible: middleLoginItem.visible
    property alias middleRegisterItemVisible: middleRegisterItem.visible

    Item {
        id: header
        width: parent.width
        height: parent.height * 0.3
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
                    middleLoginItemVisible = false
                    middleRegisterItemVisible = false
                    middleItemVisibe = true
                }
            }
        }
        Image {
            id: retn
            source: "../images/leftArea/showAllCreatedSongList.png"
            width: 20
            height: 20
            rotation: 180
            visible: middleItemVisibe ? false : true
            anchors{
                top:parent.top
                topMargin: 10
                left: parent.left
                leftMargin: 10
            }
            MouseArea {
                anchors.fill: retn
                focus: true
                acceptedButtons: Qt.LeftButton
                onClicked: {
                    returnClicked()
                }
            }
        }

        //对话框的拖动
        MouseArea {
            anchors {
                left: parent.left
                leftMargin: 30
                bottom: parent.bottom
                top: parent.top
                right: parent.right
                rightMargin: 30
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
    Item{
        id:middleItem
        width: parent.width
        height: parent.height * 0.7
        anchors{
            top:header.bottom
            left: parent.left
            right: parent.right
        }
        MyButton {
            id: login
            width: parent.width * 0.7
            height: 40
            radius: 20
            anchors {
                left: parent.left
                leftMargin: 35
                top: parent.top
            }
            text: "帐号登录"
            onButtonClicked: userLoginClicked()
        }
        MyButton {
            id: register
            width: parent.width * 0.7
            height: login.height
            radius: 20
            anchors {
                top: login.bottom
                topMargin: 20
                left: parent.left
                leftMargin: 35
            }
            text: "注册"
            onButtonClicked: userRegisterClicked()
        }
    }
    Item{
        id:middleLoginItem
        width: parent.width
        height: parent.height * 0.7
        visible: false//middleItemVisibe ? false :(middleRegisterItemVisible ? false : true)
        anchors{
            top:header.bottom
            left: parent.left
            right: parent.right
        }
        MyTextInput{
            id:loginUserName
            width: parent.width * 0.7
            height: 40
            maxTextLength: 11
            anchors{
                top:parent.top
                left: parent.left
                leftMargin: 35
            }
            remindText: loginUserName.text == "" ? "输入用户名":""
            text:middleLoginItem.visible ? loginUserName.text : ""
        }
        MyTextInput{
            id:loginUserPassword
            width: parent.width * 0.7
            height: 40
             maxTextLength: 11
            anchors{
                top:loginUserName.bottom
                left: parent.left
                leftMargin: 35
            }
            remindText: loginUserPassword.text == "" ? "输入密码":""
            text:middleLoginItem.visible ? loginUserPassword.text : ""
            onTextAccepted: {
            }
        }
        MyButton{
            id:loginButton
            width: loginUserName.width
            height: loginUserName.height
            color: "red"
            anchors{
                top:loginUserPassword.bottom
                topMargin: 10
                left: parent.left
                leftMargin: 35
            }
            text: "登录"
        }
    }
    Item{
        id:middleRegisterItem
        width: parent.width
        height: parent.height * 0.6
        visible:false
        anchors{
            top:header.bottom
            left: parent.left
        }
        MyTextInput{
            id:registerUserName
            width: parent.width * 0.7
            height: 40
             maxTextLength: 11
            anchors{
                top:parent.top
                left: parent.left
                leftMargin: 35
            }
            remindText: registerUserName.text == "" ? "输入用户名":""
            text:middleRegisterItem.visible ? registerUserName.text : ""
        }
        MyTextInput{
            id:registerUserPassword
            width: parent.width * 0.7
            height: 40
             maxTextLength: 11
            anchors{
                top:registerUserName.bottom
                left: parent.left
                leftMargin: 35
            }
            remindText: registerUserPassword.text == "" ? "输入密码，至少6位":""
            text:middleRegisterItem.visible ? registerUserPassword.text : ""
            onTextAccepted: {

            }
        }
        MyButton{
            id:registerButton
            width: registerUserName.width
            height: registerUserName.height
            color:"red"
            anchors{
                top:registerUserPassword.bottom
                topMargin: 10
                left: parent.left
                leftMargin: 35
            }
            text: "注册"
        }
    }

    //    Item {
    //        id: bottomitem
    //        width: parent.width
    //        height: parent.height * 0.2
    //        anchors.top: header.bottom
    //        anchors.bottom: parent.bottom
    //        anchors.left: parent.left
    //        anchors.right: parent.right

    //        ImageButton {
    //            id: weixin
    //            width: 50
    //            height: 60
    //            radius: 20
    //            anchors {
    //                left: parent.left
    //                leftMargin: 50
    //                top: parent.top
    //                topMargin: 10
    //            }
    //            source: "../images/cloudMusic.ico"
    //            text: "微信"
    //        }
    //        ImageButton {
    //            width: 50
    //            height: 60
    //            radius: 20
    //            anchors {
    //                left: weixin.right
    //                leftMargin: 20
    //                top: parent.top
    //                topMargin: 10
    //            }
    //            text: "QQ"
    //            source: "../images/cloudMusic.ico"
    //        }
    //    }
}
