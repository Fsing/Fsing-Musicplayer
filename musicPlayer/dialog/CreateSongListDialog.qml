import QtQuick 2.9
import QtQuick.Controls 2.2

Popup {
    id: popup
    x: mainWindow.width / 2 - 150
    //    y: mainWindow.height / 2 + 200
    y: 100

    signal inputAccepted
    property var inputText: ""

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
    dim: false
    enabled: true
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
