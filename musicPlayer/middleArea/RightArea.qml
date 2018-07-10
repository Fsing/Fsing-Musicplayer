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

    property var songListInfo

    Connections {
        target: mainWindow
        onStartSearch: {
            console.log("search")
            stackView.push(searchComponent)
        }
    }

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
        id: searchComponent
        Search {
            id: search
        }
    }
    Component {
        id: favoriteComponent
        MyFavorite {
            id: favorite
        }
    }
    Component {
        id: mySongListComponent
        SongList {
            id: mysongList
            songListId: {
                songListInfo[0]
                console.log("RightAreasonglistID:           " + songListInfo[0])
            }
            listname: songListInfo[1]
            username: songListInfo[2]
            createTime: songListInfo[3]
            model: songsModel
            listImg: "file:///" + applicationDirPath + "/" + songListInfo[6]
            label: songListInfo[4]
            briefInfo: songListInfo[5]
        }
    }

    ListModel {
        id: songsModel
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

        client.fileTransfer(interfaceParamter[80])
        client.fileTransfer(interfaceParamter[81])
        client.fileTransfer(interfaceParamter[82])
        client.fileTransfer(interfaceParamter[83])
        client.fileTransfer(interfaceParamter[84])
        client.fileTransfer(interfaceParamter[85])
        stackView.push(findMusicComponent)
    }

    function appendSong(id) {
        var list = client.getSongListSongs(id)
        var count = client.getSongListCount()
        songsModel.clear()
        for (var i = 0; i < count; ++i) {
            songsModel.append({
                                  album: list[i * 8 + 3],
                                  id: list[i * 8],
                                  name: list[i * 8 + 1],
                                  playQuantity: list[i * 8 + 5],
                                  singer: list[i * 8 + 2],
                                  source: list[i * 8 + 4]
                              })
        }
    }
}
