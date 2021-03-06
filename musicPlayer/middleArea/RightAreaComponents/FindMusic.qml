import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4
import QtQml.Models 2.2
import QtQuick.Layouts 1.2
import "../../songList"

Rectangle {
    id: findMusicRetangle
    property int index: 0
    property var interfaceParamter: client.getinterface()
    property var songListInformation
    signal clickedSongList(var clickedSongListId)

    Connections {
        target: mainWindow
        onLeftButtonPressed: {
            findMusicstackView.pop(findMusicPage)
            listmodel1.clear()
        }
    }
    Connections {
        target: findMusicRetangle
        onClickedSongList: {
            songListInformation = client.getSongListInformation(
                        clickedSongListId)
            findMusicstackView.push(songListPage)
        }
    }
    StackView {
        id: findMusicstackView
        anchors {
            top: parent.top
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
        width: 825

        visible: true
        initialItem: findMusicPage
        Component {
            id: findMusicPage
            ScrollView {
                id: scrollView
                anchors.fill: parent
                verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff
                horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
                ColumnLayout {
                    Advert {
                        id: advert
                        modle: advertListmodle
                        Layout.fillWidth: true
                    }

                    GridLayout {
                        columns: 4
                        anchors.top: advert.bottom
                        anchors.left: advert.left
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {
                                playQuantity: interfaceParamter[7]
                                source: "file:///" + applicationDirPath + "/" + interfaceParamter[6]
                                songlistId: interfaceParamter[0]
                                songlistName: interfaceParamter[1]
                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {
                                playQuantity: interfaceParamter[17]
                                source: "file:///" + applicationDirPath + "/"
                                        + interfaceParamter[16]
                                songlistId: interfaceParamter[10]
                                songlistName: interfaceParamter[11]
                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {
                                playQuantity: interfaceParamter[27]
                                source: "file:///" + applicationDirPath + "/"
                                        + interfaceParamter[26]
                                songlistId: interfaceParamter[20]
                                songlistName: interfaceParamter[21]
                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {
                                playQuantity: interfaceParamter[37]
                                source: "file:///" + applicationDirPath + "/"
                                        + interfaceParamter[36]
                                songlistId: interfaceParamter[30]
                                songlistName: interfaceParamter[31]
                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {
                                playQuantity: interfaceParamter[47]
                                source: "file:///" + applicationDirPath + "/"
                                        + interfaceParamter[46]
                                songlistId: interfaceParamter[40]
                                songlistName: interfaceParamter[41]
                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {
                                playQuantity: interfaceParamter[57]
                                source: "file:///" + applicationDirPath + "/"
                                        + interfaceParamter[56]
                                songlistId: interfaceParamter[50]
                                songlistName: interfaceParamter[51]
                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {
                                playQuantity: interfaceParamter[67]
                                source: "file:///" + applicationDirPath + "/"
                                        + interfaceParamter[66]
                                songlistId: interfaceParamter[60]
                                songlistName: interfaceParamter[61]
                            }
                        }
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.minimumWidth: 200
                            Layout.maximumHeight: 300
                            Layout.maximumWidth: 300
                            Layout.minimumHeight: 200
                            SongListRectangle {
                                playQuantity: interfaceParamter[77]
                                source: "file:///" + applicationDirPath + "/"
                                        + interfaceParamter[76]
                                songlistId: interfaceParamter[70]
                                songlistName: interfaceParamter[71]
                            }
                        }
                    }
                }
            }
        }
        Component {
            id: songListPage
            SongList {
                id: songlists
                width: parent.width
                height: parent.height
                model: listmodel1
                songListId: songListInformation[0]
                userImg: "qrc:/images/logo.jpg"
                createTime: songListInformation[3]

                listname: songListInformation[1]
                listImg: "file:///" + applicationDirPath + "/" + songListInformation[6]
                label: songListInformation[4]
                briefInfo: songListInformation[5]
                username: songListInformation[2]
            }
        }
    }

    ListModel {
        id: listmodel1
    }
    ListModel {
        id: advertListmodle
    }
    Timer {
        interval: 100
        running: true
        onTriggered: advertAppend()
    }

    function advertAppend() {

        console.log(interfaceParamter)
        for (var i = 0; i < 6; ++i) {
            advertListmodle.append({
                                       advertImg: "file:///" + applicationDirPath
                                                  + "/" + interfaceParamter[i + 80]
                                   })
        }
    }

    function appendSong(id) {
        var list = client.getSongListSongs(id)
        var count = client.getSongListCount()
        for (var i = 0; i < count; ++i) {

            listmodel1.append({
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
