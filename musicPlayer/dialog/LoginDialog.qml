import QtQuick 2.0
import QtQuick.Controls 2.1
import "./common"

CommonDialog{
    id:loginDialog
    width: 300
    height: 400
    contentItem:LoginDialogItem {
        onUserLoginClicked:{
            middleItemVisibe = false
            middleLoginItemVisible = true
        }
        onUserRegisterClicked:{
            middleItemVisibe = false
            middleRegisterItemVisible = true
        }
        onReturnClicked:{
            middleLoginItemVisible = false
            middleRegisterItemVisible = false
            middleItemVisibe = true
        }
        onLoginClicked: {

        }
        onRegisterClicked: {
//            mainWindow
        }
    }
}
