import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtMultimedia 5.2
import "topArea"
import "middleArea"
import "bottomArea"
import "./dialog"
import LyricObject 1.0

Window {
    id: mainWindow
    visible: true
    title: "netMusic"

    //最小窗口大小
    minimumWidth: 1025
    minimumHeight: 670
    //无边框flag
    flags: Qt.Window | Qt.FramelessWindowHint

    signal selectSong(string song)
    signal positionChange(int positions)

    //---------------------top栏
    TopArea {
        id: topArea
    }
    //---------------------middle栏
    MiddleArea {
        id: middleArea
    }

    //---------------------bottom栏
    BottomArea {
        id: bottomArea
    }

}
