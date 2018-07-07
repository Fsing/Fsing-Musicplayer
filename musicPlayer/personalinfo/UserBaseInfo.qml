import QtQuick 2.0
import QtQuick.Layouts 1.1
import "./element"

Rectangle{
    Row{
        anchors.fill: parent
        spacing: 30
        UserIcon{
            id:userIcon
            width: 200
            height: 200
        }
        RightBaseInfo{
            id:rightBaseInfo
            width: parent.width-200-10
            height: parent.height
        }
    }
}
