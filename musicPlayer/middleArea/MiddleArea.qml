import QtQuick 2.0
import QtQuick.Controls 1.4
import "../personalinfo"

Rectangle {
    anchors.top: topArea.bottom
    anchors.bottom: bottomArea.top
    anchors.left: parent.left
    anchors.right: parent.right
    color: "white"

    property var listmodel: leftArea.listmodel
    property alias leftArea: leftArea
    property alias personal: personal
    property alias allAttentions: allAttentions
    property alias attentedUserModel: allAttentions.attenedUsersModel
    property alias rightAreaaDownload: rightArea.downloadModel2

    LeftArea {
        id: leftArea
    }
    RightArea {
        id: rightArea
        PersonalInformation {
            id: personal
            visible: false
            createdSongListNumber: client.createdSongListCount
            collectedSongListNumber: client.collecedSongListCount
            attentions: client.attentionUserCount
            fans: client.fanUserCount
            userName: client.userName
            userIcon: "file:///" + applicationDirPath + "/" + client.userIcon
        }

        AllAttentions {
            id: allAttentions
            visible: false
        }
    }
}
