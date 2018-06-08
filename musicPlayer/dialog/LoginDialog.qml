import QtQuick 2.0
import QtQuick.Controls 2.1

Popup {
    id: loginDialog
    x: parent.width / 2 - 150
    y: 100

    signal inputAccepted
    property string inputText: ""

    width: 300
    height: 400
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape
    contentItem: LoginDialogItem {
    }
    dim: false
}
