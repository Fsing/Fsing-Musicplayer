import QtQuick 2.0
import "../../personalinfo"


Rectangle {
    property int index: 2
//    color: "red"
//    Text {
//        anchors.centerIn: parent
//        text: qsTr("Mv")
//    }
    PersonalInformation{
        id:personalInformation
        createdSongListNumber:{
            console.log(client.createdSongListCount())
            console.log("hahahah")
            client.createdSongListCount()
        }
        collectedSongListNumber: client.collectedSongListCount()
    }
}
