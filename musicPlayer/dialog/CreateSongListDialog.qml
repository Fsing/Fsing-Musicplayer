import QtQuick 2.2
import QtQuick.Controls 2.1

Popup {
    id: popup
    x: mainWindow.width / 2 - 150
    //    y: mainWindow.height / 2 + 200
    y: 100

    signal inputAccepted
    property string inputText: ""

    width: 300
    height: 300
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape
    contentItem: CreateSongistDialogItem {
        onQuitClicked: popup.close()
        onOkButtonClicked: {
            popup.close()
            inputAccepted()
        }
    }
    dim: false //是否背景变暗
    //enabled: true
    //    implicitHeight: 300
    //    implicitWidth: 300
    //    enter: Transition {
    //        NumberAnimation {
    //            property: "opacity"
    //            from: 0.0
    //            to: 1.0
    //        }
    //    }
    //    exit: Transition {
    //        NumberAnimation {
    //            property: "opacity"
    //            from: 1.0
    //            to: 0.0
    //        }
    //    }
}
