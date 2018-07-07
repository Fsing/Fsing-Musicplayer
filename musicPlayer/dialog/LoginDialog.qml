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
            remindMessageVisible = ""
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
            setRemindMessage(client.result)
            console.log(client.result)
            if (client.logining) {
                topRightButton.loginButtonSource = "qrc:/images/logo.jpg"
                var i = 0
//                console.log(client.createdSongLists()[i])
                while (client.createdSongLists()[i]) {
                    if(middleArea.leftArea.showAllCreateClicked){
                        middleArea.listmodel.append({
                                                        recColor: "#F5F5F7",
                                                        imagesource: "../images/leftArea/list.png",
                                                        tx: client.createdSongLists()[i],
                                                        opaci: 0.55,
                                                        classifyText: "",
                                                        delegate_listVisible: true
                                                    })
                    }else{
                        middleArea.listmodel.append({
                                                        recColor: "#F5F5F7",
                                                        imagesource: "../images/leftArea/list.png",
                                                        tx: client.createdSongLists()[i],
                                                        opaci: 0.55,
                                                        classifyText: "",
                                                        delegate_listVisible: false
                                                    })
                    }

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
