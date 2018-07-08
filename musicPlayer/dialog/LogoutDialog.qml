import QtQuick 2.0
import "./common"

CommonDialog {
    id: logoutDialog

    width: 300
    height: 300
    contentItem: LogoutDialogItem {
        onLogoutClick: {
            client.logining = false
            client.userName = ''
            topRightButton.fanName = "未登录"
            topRightButton.loginButtonSource = "qrc:/images/common/ac0.png"
            logoutDialog.close()
            var i = 0
            console.log(middleArea.listmodel.count)
            while (client.createdSongLists()[i]) {
                middleArea.listmodel.remove(middleArea.listmodel.count - 1)
                i++
            }
            console.log(middleArea.listmodel.count)
        }
    }
}
