import QtQuick 2.0
import QtQuick.Controls 2.1
import "./common"

CommonDialog {
    id: loginDialog
    width: 300
    height: 400

    contentItem: LoginDialogItem {
        onUserLoginClicked: {
            middleItemVisibe = false
            middleLoginItemVisible = true
        }
        onUserRegisterClicked: {
            middleItemVisibe = false
            middleRegisterItemVisible = true
            remindMessageVisible = ""
        }
        onReturnClicked: {
            middleLoginItemVisible = false
            middleRegisterItemVisible = false
            middleItemVisibe = true
        }
        onLoginClicked: {
            mainWindow.client.myLogin(loginUserNameText, loginUserPasswordText)
            console.log(client.result)
            if (client.logining) {
                topRightButton.loginButtonSource = "qrc:/images/logo.jpg"
                var i = 0
                console.log("songlistnames" + client.songlistNames()[i])
                //                var str = client.songliseNames()[i]
                while (client.songlistNames()[i]) {
                    middleArea.listmodel.append({
                                                    recColor: "#F5F5F7",
                                                    imagesource: "../images/leftArea/list.png",
                                                    tx: client.songlistNames(
                                                            )[i],
                                                    opaci: 0.55,
                                                    classifyText: "",
                                                    delegate_listVisible: true
                                                })
                    i++
                }
            }
        }
        onRegisterClicked: {
            mainWindow.client.myRegister(registerUserNameText,
                                         registerUserPasswordText)
            setRemindMessage(client.result)
            console.log(client.result)
        }
    }
}
