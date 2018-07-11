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
    property alias stackView: stackView
    property alias searchComponent: searchComponent
    //    property alias searchMusicModel: searchMusicModel

    //    Connections {
    //        target: mainWindow
    //        onStartSearch: {
    //            console.log("search--------------------------------")
    //            stackView.push(searchComponent)
    //        }
    //    }
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
            console.log("Js.popView(n)" + n)
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
            searchModel: searchMusicModel
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

    ListModel {
        id: searchMusicModel
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

    function searchSongs(searchlist, listcount) {
        var list = searchlist
        var count = listcount
        console.log("searchlist[0]: " + list[0])
        console.log("searchlist[1]: " + list[1])
        console.log("searchlist[2]: " + list[2])
        console.log("listcount： " + count)
        searchMusicModel.clear()
        for (var i = 0; i < count; ++i) {
            searchMusicModel.append({
                                        salbum: list[i * 8 + 3],
                                        sid: list[i * 8],
                                        sname: list[i * 8 + 1],
                                        splayQuantity: list[i * 8 + 5],
                                        ssinger: list[i * 8 + 2],
                                        ssource: list[i * 8 + 4]
                                    })
        }
        console.log("searchMusicModel: " + searchMusicModel.count)
    }

    function appendSongs(id) {
        var list = client.getSongListSongsFromServer(id)
        var count = client.getSongListSongCount()
        songsModel.clear()
        console.log("=============: " + list[0])
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
        console.log("jiegou: " + (count - 1) * 8 + 5)
    }
}
