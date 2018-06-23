import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Window 2.0

Rectangle {
    width: 250
    height: parent.height
    anchors.right: parent.right
    anchors.rightMargin: 5
    color: parent.color

    signal loginButtonClicked

    Button {
        id: closebutton
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        width: 18
        height: 18
        MouseArea{
            id: closeButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: Qt.quit()
        }

        background: Image {
            id:leftButtonImage
            anchors.fill: parent
            opacity: closeButtonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/topArea/close.png"
        }
    }
    Button {
        id: maxbutton
        anchors.right: closebutton.left
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        width: 18
        height: 18
        MouseArea{
            id: maxButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                if(mainWindow.visibility === Window.FullScreen){
                    mainWindow.width =1025
                    mainWindow.height =670
                    mainWindow.setX(xPosition)
                    mainWindow.setY(yPosition)
                }
                else {
                    xPosition = mainWindow.x
                    yPosition = mainWindow.y
                mainWindow.visibility = Window.FullScreen
                }
            }
        }

        background:
            Rectangle{
                id: maxButton;
                anchors.centerIn: parent;
                width: 14;
                height: 11;
                border.width: 1;
                border.color: maxButtonMouseArea.containsMouse ? "#FFFFFF" : "#E29595";
                color: "#C62F2F";
                radius: 2;
            }
        }
    Button {
        id: minbutton
        anchors.right: maxbutton.left
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        width: 18
        height: 18
        MouseArea{
            id: minButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: mainWindow.visibility = Window.Minimized
        }

        background: Image {
            id:minButtonImage
            anchors.fill: parent
            opacity: minButtonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/topArea/mini.png"
        }
    }
    Rectangle {
        id:rec
        width: 1
        height: 18
        anchors.right: minbutton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        color: "#a82828"
    }
    Button {
        id: settingbutton
        anchors.right: rec.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 16
        height: 16
        MouseArea{
            id: settingbuttonMouseArea
            anchors.fill: parent
            hoverEnabled: true
        }

        background: Image {
            id:settingbuttonImage
            anchors.fill: parent
            opacity: settingbuttonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/topArea/setting1.png"
        }
    }
    Button {
        id: emailbutton
        anchors.right: settingbutton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 16
        height: 16
        MouseArea{
            id: emailbuttonMouseArea
            anchors.fill: parent
            hoverEnabled: true
        }

        background: Image {
            id:emailbuttonImage
            anchors.fill: parent
            opacity: emailbuttonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/topArea/message.png"
        }
    }
    Button {
        id: skinbutton
        anchors.right: emailbutton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 16
        height: 16
        MouseArea{
            id: skinbuttonMouseArea
            anchors.fill: parent
            hoverEnabled: true
        }

        background: Image {
            id:skinbuttonImage
            anchors.fill: parent
            opacity: skinbuttonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/topArea/skin.png"
        }
    }
    Button {
        id: loginbutton
        anchors.right: skinbutton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 16
        height: 16
        MouseArea{
            id: loginbuttonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: loginButtonClicked()
        }

        background: Image {
            id:loginbuttonImage
            anchors.fill: parent
            opacity: loginbuttonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/topArea/skin.png"
        }
    }
}
