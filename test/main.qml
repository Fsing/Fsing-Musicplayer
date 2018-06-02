import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtMultimedia 5.2

Window {
    id:mainWindow
    visible: true
    minimumWidth: 1025
    minimumHeight: 670
    color: "#F6F6F8"
    flags: Qt.FramelessWindowHint

    //--------------------top栏
    Rectangle {
        width: parent.width
        height: 50
        color: "#C62F2F"

    MouseArea {//top栏拖动
            x: parent.left
            width: parent.width - 5
            height: parent.height
            acceptedButtons: Qt.LeftButton
            property point clickPos: "0,0"
            onPressed: {
                    clickPos  = Qt.point(mouse.x,mouse.y)
            }
            onPositionChanged: {
                    var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
                    mainWindow.setX(mainWindow.x+delta.x)
                    mainWindow.setY(mainWindow.y+delta.y)
            }
        }

    MouseArea {//top栏右侧 可拖动窗口大小
        width: 5
        height: parent.height
        x: parent.width-5
        acceptedButtons: Qt.LeftButton
        property point clickPos: "0,0"
        onPressed: {
                clickPos  = Qt.point(mouse.x,mouse.y)

        }
        onPositionChanged: {
                var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            if(mainWindow.width+delta.x <= 1025){
            }else {
            mainWindow.setWidth(mainWindow.width+delta.x)
            }
        }
    }
    }

    //-----------bottom栏
    Rectangle {
        y:parent.height - 50
        width: parent.width
        height: 50
        color: "#C62F2F"
    }

}

