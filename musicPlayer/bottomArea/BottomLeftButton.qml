import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    width: 200
    height: parent.height
    anchors.left: parent.left
    color: parent.color

    Button {
        id: prebutton
        anchors.left: parent.left
        anchors.leftMargin: 40
        anchors.verticalCenter: parent.verticalCenter
        width: 32
        height: 32

        MouseArea{
            id: preButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                var previousIndex = mediaPlayer.playlist.previousIndex()
                if (previousIndex === -1) {
                    mediaPlayer.playlist.currentIndex = mediaPlayer.playlist.itemCount - 1
                } else {
                    mediaPlayer.playlist.previous()
                }
                mediaPlayer.play()
                songChanged(currentPlaylist.currentItemSource)
            }
        }
        background:Rectangle{
            id:preButtonRectangle
            anchors.fill: parent
            color: "#C62F2F"
            radius: 30
            Image {
                        id:preButtonImage
                        anchors.centerIn:parent
                        opacity: preButtonMouseArea.containsMouse ? 0.8 : 1.0
                        source: "qrc:/images/bottomArea/previous.png"
                    }
        }
    }
    Button {
        id: pausebutton
        anchors.left: prebutton.right
        anchors.leftMargin: 20
        anchors.verticalCenter: prebutton.verticalCenter
        width: 40
        height: 40

        MouseArea{
            id: pauseButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                console.log(mediaPlayer.playbackState)
                if(mediaPlayer.playbackState === 1)
                            mediaPlayer.pause()
                else
                    mediaPlayer.play()
            }
        }
        background:Rectangle{
            id:pauseButtonRectangle
            anchors.fill: parent
            color: "#C62F2F"
            radius: 30
            Image {
                        width: 44
                        height: 44
                        id:pauseButtonImage
                        anchors.centerIn:parent
                        opacity: pauseButtonMouseArea.containsMouse ? 0.8 : 1.0
                        source: mediaPlayer.playbackState === 1 ?
                            "qrc:/images/bottomArea/pause.png"
                                  : "qrc:/images/bottomArea/play.png"
                    }
        }
    }
    Button {
        id: nextbutton
        anchors.left: pausebutton.right
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 32
        height: 32

        MouseArea{
            id: nextButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                var nextIndex = mediaPlayer.playlist.nextIndex()
                if (nextIndex === -1) {
                    mediaPlayer.playlist.currentIndex = 0
                } else {
                    mediaPlayer.playlist.next()
                }
                mediaPlayer.play()
                songChanged(currentPlaylist.currentItemSource)
            }
        }
        background:Rectangle{
            id:nextButtonRectangle
            anchors.fill: parent
            color: "#C62F2F"
            radius: 30
            Image {
                        id:nextButtonImage
                        anchors.centerIn:parent
                        opacity: nextButtonMouseArea.containsMouse ? 0.8 : 1.0
                        source: "qrc:/images/bottomArea/next.png"
                    }
        }
    }


}
