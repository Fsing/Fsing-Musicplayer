import QtQuick 2.0
import "../dialog/common"

CommonDialog {
    id: collectSongDialog
    property alias collectSongModel: collectsongItem.collectSongModel

    width: 200
    height: collectsongItem.height + 20
    contentItem: CollectSongItem {
        id: collectsongItem
        onCreateSongList: {
            leftArea.createSongListDialog.open()
            collectSongDialog.close()
            songOperationDialog.close()
        }
        onCollectSongToSongList: {

        }
    }
}
