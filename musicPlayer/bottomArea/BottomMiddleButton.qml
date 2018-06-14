import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    width: 270
    height: parent.height
    anchors.left: bottomLeftButton.right
    anchors.right: bottomRightButton.left
    color: parent.color

    Text {
        id: totalTime
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        text: mediaPlayer.duration
    }
    Text {
        id: currentTime
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        text: mediaPlayer.position
    }
    Slider {
        id: positionSlider
        anchors.left: currentTime.right
        anchors.right: totalTime.left
        anchors.leftMargin: 5
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        from: 0.0
        to: 1.0
        value: mediaPlayer.position / mediaPlayer.duration

        handle: Rectangle {
            id: handleRectangle
            visible: true
            x: positionSlider.value * positionSlider.width
            y: positionSlider.topPadding + positionSlider.availableHeight / 2 - height / 2
            implicitWidth: 14
            implicitHeight: 14
            radius: 13
            border.width: 1
            border.color: "#E1E1E2"
            Rectangle {
                width: 4
                height: 4
                color: "red"
                radius: 13
                anchors.centerIn: parent
            }
        }
        Rectangle {
            anchors.left: positionSlider.left
            anchors.leftMargin: 6
            anchors.right: handleRectangle.left
            y: positionSlider.topPadding + positionSlider.availableHeight / 2 - height / 2
            radius: 13
            height: 4
            color: "red"
        }
    }
}
