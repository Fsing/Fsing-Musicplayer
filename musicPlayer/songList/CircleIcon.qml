import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    width: 30
    height: 30
    property string source: img.source

    Image {
        id: img
        source: "../images/logo.jpg"
        sourceSize: Qt.size(parent.width, parent.height)
        anchors.fill: parent
        smooth: true
        visible: false
    }

    //轮廓
    Rectangle {
        id: mask
        smooth: true
        visible: false
        anchors.fill: parent
        radius: height / 2
    }

    OpacityMask {
        anchors.fill: img
        source: img
        maskSource: mask
    }
}
