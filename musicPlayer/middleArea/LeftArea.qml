import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 1.4

Rectangle {
    id: rec_parent
    width: parent.width * 0.2
    height: 570 //topArea.height - bottomArea.height
    color: "#F5F5F7"

    //    border.width: 1
    //    border.color: leftAreaBorderColor

    //    anchors.top: parent.top
    //    anchors.left: parent.left
    //    property var leftAreaBorderColor: "Silver"
    property int modelindex: -1
    property bool showAllCreateClicked: false
    property int creatIndex: 9
    property int maxIndex: listModel.count

    ScrollView {
        id: leftItem
        anchors.fill: parent
        clip: true
        style: ScrollViewStyle {
            id: ss
            transientScrollBars: true
        }
        ListView {
            id: listView
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 15
            anchors.left: parent.left
            spacing: 10
            width: rec_parent.width - 10
            height: rec_parent.height
            model: listModel
            delegate: delegates
        }
    }

    Component {
        id: delegates
        LeftItem {
            width: parent.width - 10
            height: classfify.visible ? 50 : 25
        }
    }
    ListModel {
        id: listModel
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/sound.png"
            tx: "发现音乐"
            opaci: 0.55
            classifyVisible: true
            classifyText: "推荐"
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/btnradio2.png"
            tx: "私人FM"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/btnmv.png"
            tx: "MV"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/btnfriends.png"
            tx: "朋友"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/localMusic.png"
            tx: "本地音乐"
            opaci: 0.55
            classifyVisible: true
            classifyText: "我的音乐"
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/btndownload.png"
            tx: "下载管理"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/sound.png"
            tx: "我的音乐云盘"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/sound.png"
            tx: "我的歌手"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/btnmv.png"
            tx: "我的MV"
            opaci: 0.55
            classifyText: ""
            delegate_listVisible: true
        }
        ListElement {
            recColor: "#F5F5F7"
            imagesource: "../images/leftArea/btnfavorite.png"
            tx: "我喜欢的音乐"
            opaci: 0.55
            classifyVisible: true
            classifyText: "创建的歌单"
            showAllCreateVisible: true
            delegate_listVisible: false
        }
    }

    onShowAllCreateClickedChanged: {
        if (rec_parent.showAllCreateClicked) {
            var i = maxIndex - 1
            for (i; i >= creatIndex; i--) {
                listModel.setProperty(i, "delegate_listVisible", true)
            }
            //                listModel.append({
            //                                     recColor: "#F5F5F7",
            //                                     imagesource: "../images/leftArea/btnmv.png",
            //                                     tx: "favorite",
            //                                     opaci: 0.55,
            //                                     classifyText: "",
            //                                     delegate_listVisible: false
            //                                 })
        } else {
            var j = maxIndex - 1
            for (j; j >= creatIndex; j--) {
                listModel.setProperty(j, "delegate_listVisible", false)
            }
        }
    }
}
