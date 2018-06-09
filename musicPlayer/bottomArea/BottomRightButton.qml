import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls.Styles 1.4

Rectangle {
    width: 290
    height: parent.height
    anchors.right: parent.right
    anchors.rightMargin: 5
    color: parent.color

    Button {
        id: songlistButton
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 18
        height: 18
        MouseArea{
            id: songlistButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
        }

        background: Image {
            id:songlistButtonImage
            anchors.fill: parent
            opacity: songlistButtonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/bottomArea/songlist.png"
        }
    }
    Button {
        id: liricButton
        anchors.right: songlistButton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 18
        height: 18
        MouseArea{
            id: liricButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
        }

        background: Image {
            id:liricButtonnImage
            anchors.fill: parent
            opacity: liricButtonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/bottomArea/liric.png"
        }
    }

    Button {
        id: orderButton
        anchors.right: liricButton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 18
        height: 18
        property int index: 0
        state: "sequence"
        states: [
            State {
                name: "sequence"
                PropertyChanges { target: orderButtonImage
                          source: "qrc:/images/bottomArea/sequence.png" }
            },
            State {
                name: "circle"
                PropertyChanges { target: orderButtonImage;
                    source: "qrc:/images/bottomArea/circle.png" }
            },
            State {
                name: "single"
                PropertyChanges { target: orderButtonImage;
                    source: "qrc:/images/bottomArea/single.png" }
            },
            State {
                name: "random"
                PropertyChanges { target: orderButtonImage;
                    source: "qrc:/images/bottomArea/random.png" }
            }
        ]
        MouseArea{
            id: orderButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
            onClicked: {
                console.log(parent.state)
                if(parent.state === "sequence"){
                    parent.state = "circle"
                }else if(parent.state === "circle"){
                   parent.state = "single"
                }else if(parent.state === "single"){
                    parent.state = "random"
                }else if(parent.state === "random"){
                    parent.state = "sequence"
                }
            }
        }
        background: Image {
            id:orderButtonImage
            anchors.fill: parent
            opacity: orderButtonMouseArea.containsMouse ? 1.0 : 0.5
        }
    }
    Slider{
        id: voiceSlider
        anchors.right: orderButton.left
        anchors.rightMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        width: 120;
        from:0.0
        to:1.0
        value: 0.5

        handle: Rectangle {
            id:handleRectangle
            visible: sliderMouseArea.containsMouse ? true : false
            x: voiceSlider.leftPadding + voiceSlider.visualPosition * (voiceSlider.availableWidth - width)
            y: voiceSlider.topPadding + voiceSlider.availableHeight / 2 - height / 2
            implicitWidth: 14
            implicitHeight: 14
            radius: 13
            border.width: 1;
            border.color: "#E1E1E2";
            Rectangle{
                width: 4;
                height: 4;
                color: "red";
                radius: 13;
                anchors.centerIn: parent;
            }
        }
        Rectangle {
            anchors.left: voiceSlider.left
            anchors.leftMargin: 6
            anchors.right: handleRectangle.left
            y: voiceSlider.topPadding + voiceSlider.availableHeight / 2 - height / 2
            radius: 13
            height: 4
            color: "red"
        }
    MouseArea {
        id:sliderMouseArea
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true

        onPressed: mouse.accepted = false
    }
    }

    Button {
        id: voiceButton
        anchors.right: voiceSlider.left
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        width: 18
        height: 18
        MouseArea{
            id: voiceButtonMouseArea
            anchors.fill: parent
            hoverEnabled: true
        }

        background: Image {
            id:voiceButtonImage
            anchors.fill: parent
            opacity: voiceButtonMouseArea.containsMouse ? 1.0 : 0.5
            source: "qrc:/images/bottomArea/voice.png"
        }
    }
}
