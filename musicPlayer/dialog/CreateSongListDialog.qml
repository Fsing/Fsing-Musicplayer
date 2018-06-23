import QtQuick 2.2
import QtQuick.Controls 2.1
import "common"

CommonDialog {
    id: createSongListDialog

    signal inputAccepted
    property string inputText: ""

    width: 300
    height: 300
    contentItem: CreateSongistDialogItem {
        onQuitClicked: createSongListDialog.close()
        onOkButtonClicked: {
            createSongListDialog.close()
            inputAccepted()
        }
    }
}
