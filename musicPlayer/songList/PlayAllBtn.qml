import QtQuick 2.0
import QtQuick.Controls 2.4

Item {
    width: playImg.width + 1 + textImg.width
    height: playImg.height
    Button {
        id: playImg
        icon.source: "../images/bottomArea/play.png"
        text: "播放全部"
    }
    Rectangle {
        id: line
        //模拟线段
        width: 1 //长
        height: playImg.height //高
        anchors.left: playImg.right
        anchors.bottom: playImg.bottom
        visible: true
        color: "#7c7171" //颜色
    }

    Button {
        id: textImg
        width: 30
        anchors.left: playImg.right
        anchors.leftMargin: 1
        icon.source: "../images/leftArea/creatSongList.png"
    }
}
