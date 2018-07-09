import QtQuick 2.5
import QtQuick.Controls 2.1
import "../songList"
import "RightAreaComponents"
import "RightAreaJS.js" as Js

Rectangle {
    anchors.left: leftArea.right
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom

    StackView {
        id: stackView
        anchors.fill: parent

        popEnter: Transition {
            NumberAnimation {

                properties: "opacity"
                from: 0
                to: 1
                duration: 1000
            }
        }

        popExit: Transition {
            NumberAnimation {

                properties: "opacity"
                from: 1
                to: 0
                duration: 1000
            }
        }
        pushEnter: Transition {
            NumberAnimation {

                properties: "opacity"
                from: 0
                to: 1
                duration: 1000
            }
        }

        pushExit: Transition {
            NumberAnimation {

                properties: "opacity"
                from: 1
                to: 0
                duration: 1000
            }
        }
    }

    Connections {
        target: leftArea
        onLeftAreaClicked: {
            Js.popView(n)

            console.log("deepth" + stackView.depth)
        }
    }

    Component {
        id: lyricComponent
        Liric {
            id: lyric
        }
    }

    Component {
        id: findMusicComponent
        FindMusic {
            id: findMusic
        }
    }
    Component {
        id: fmComponent
        FM {
            id: fm
        }
    }
    Component {
        id: mvComponent
        Mv {
            id: mv
        }
    }
    Component {
        id: friendComponent
        Friends {
            id: friend
        }
    }
    Component {
        id: localMusicComponent

        LocalMusic {

            id: localMusic
        }
    }
    Component {
        id: downloadComponent
        Download {
            id: download
        }
    }
    Component {
        id: myMusicCloudDiskComponent
        MyMusicCloudDisk {
            id: myMusicCloudDisk
        }
    }
    Component {
        id: mySingerComponent
        MySinger {
            id: mySinger
        }
    }
    Component {
        id: myMvComponent
        MyMv {
            id: mymv
        }
    }

    Component {
        id: mySonglistComponent
        SongList {
            id: songlist
        }
    }
    Component.onCompleted: {
        stackView.push(lyricComponent)
        client.interface("FindMusic")
        var interfaceParamter = client.getinterface()
        client.fileTransfer(interfaceParamter[6])
        client.fileTransfer(interfaceParamter[16])
        client.fileTransfer(interfaceParamter[26])
        client.fileTransfer(interfaceParamter[36])
        client.fileTransfer(interfaceParamter[46])
        client.fileTransfer(interfaceParamter[56])
        client.fileTransfer(interfaceParamter[66])
        client.fileTransfer(interfaceParamter[76])
        stackView.push(findMusicComponent)

    }
}
