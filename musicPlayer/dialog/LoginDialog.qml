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
            remindMessageVisible = ""
        }
        onReturnClicked:{
            middleLoginItemVisible = false
            middleRegisterItemVisible = false
            middleItemVisibe = true
        }
        onLoginClicked: {
            mainWindow.client.myLogin(loginUserNameText,loginUserPasswordText)
            console.log(client.result)
        }
        onRegisterClicked: {
            mainWindow.client.myRegister(registerUserNameText,registerUserPasswordText)
            setRemindMessage(client.result)
            console.log(client.result)
        }
    }
}
