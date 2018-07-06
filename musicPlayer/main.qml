import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import QtQuick.Window 2.2
import QtMultimedia 5.6
import "topArea"
import "middleArea"
import "bottomArea"
import "./dialog"
import LyricObject 1.0
import Client 1.0

Window {
    id: mainWindow
    visible: true
    title: "netMusic"

    //最小窗口大小
    minimumWidth: 1025
    minimumHeight: 670
    //无边框flag
    flags: Qt.Window | Qt.FramelessWindowHint

    property alias client: client

    signal positionChange(int positions)
    signal songChanged(string song)
    signal leftButtonPressed
    signal rightButtonPressed

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

    Client{
        id:client
    }

    MediaPlayer {
        id: mediaPlayer
        autoPlay: true
        volume: 0.5
        playlist: currentPlaylist
        onPositionChanged: {
            positionChange(mediaPlayer.position)
        }
    }
    Playlist {
        id:currentPlaylist
    }

    CurrentPlayList{
         id:currentListRectangle
    }
}
