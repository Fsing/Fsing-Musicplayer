import QtQuick 2.0
import QtQuick.Controls 2.2

Rectangle {
    anchors.left: leftArea.right
    anchors.right: parent.right
    anchors.top: parent.top
    anchors.bottom: parent.bottom

    StackView {
        id: stackView
        Component.onCompleted: pushIntoStack()
    }
    Component {
        id: findMusic
        Rectangle {
            color: "blue"
        }
    }
    Component {
        id: fm
        Rectangle {
            color: "yellow"
        }
    }
    function pushIntoStack() {
        stackView.push(findMusic)
        stackView.push(fm)
    }
}
