import QtQuick 2.5
import QtMultimedia 5.8
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import LyricObject 1.0

Rectangle {
    id: rec0
    anchors.fill: parent

    property int index: -1

    LyricObject {
        id: lyric
    }
    Connections {
        target: mainWindow
        onPositionChange: {
            var i = 0
            while (i < lyricview.count) {
                if (positions > lyricview.model[i].time) {
                    i++
                } else {
                    if (i == 0) {
                        rec0.current = i
                    } else {
                        rec0.current = i - 1
                    }
                    break
                }
            }
        }
        onSongChanged: {

            lyricview.model = lyric.getLyric(song)
            console.log(song)
        }
    }

    property int current: 0
    property bool increasing: true
    ListView {
        id: lyricview
        anchors.top: parent.top
        anchors.topMargin: 50
        width: parent.width
        height: parent.height * 0.7

        spacing: 10 //每个Rectangle相隔10的单位
        displayMarginBeginning: 0
        displayMarginEnd: 0
        model: lyric.getLyric("./test")
        delegate: Rectangle {
            height: 25
            width: parent.width
            Text {
                color: if (rec0.current === index) {
                           "red"
                       } else {
                           "black"
                       }
                anchors.centerIn: parent
                text: model.modelData.text
            }
            MouseArea {
                anchors.fill: parent
                onClicked: rec0.current = index
            }
        }

        currentIndex: rec0.current
        onCurrentIndexChanged: {

            //                root.current = currentIndex
            pausetime.duration = lyricview.model[currentIndex + 1].time
                    - lyricview.model[currentIndex].time
            lyricAnimtion.restart()
            if (rec0.current == lyricview.count)
                lyricAnimtion.loops = 0
        }
    }

    //歌词
    SequentialAnimation {
        id: lyricAnimtion
        loops: lyricview.count - 1
        //        running: true
        PauseAnimation {
            id: pausetime
            duration: lyricview.model[1].time
            //            duration: 500
        }
        ScriptAction {
            script: if (rec0.increasing) {
                        rec0.current++
                        if (rec0.current >= lyricview.count - 1) {
                            //                            rec0.current = lyricview.count - 1
                            rec0.increasing = !rec0.increasing
                        }
                    }
        }
    }
}
