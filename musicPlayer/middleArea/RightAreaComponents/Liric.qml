import QtQuick 2.5
import QtMultimedia 5.8
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2
import LyricObject 1.0


Rectangle {
    id:rec0
    anchors.fill: parent

    property int index: 9

    LyricObject {
        id: lyric
    }



            property int current: 0
            property bool increasing: true
            ListView {
                id: lyricview
                width: rec0.width
                height: rec0.height

                spacing: 10 //每个Rectangle相隔10的单位

                model: lyric.getLyric("../musicPlayer/zuimei.lrc")
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
                preferredHighlightBegin: 125
                preferredHighlightEnd: 125
                highlightRangeMode: ListView.StrictlyEnforceRange
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
