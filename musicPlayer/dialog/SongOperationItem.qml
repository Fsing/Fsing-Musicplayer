import QtQuick 2.0
import QtQuick.Layouts 1.11
import "./common"

Rectangle {
    id: operationItem
    width: 280
    height: 243
    ColumnLayout {

        ButtonItem {
            utext: "查看评论"
            usource: "../../images/common/user.png"
            endImageVisible: false
        }
        ButtonItem {
            utext: "播放"
            usource: "../../images/common/user.png"
            endImageVisible: false
        }
        ButtonItem {
            utext: "下一首播放"
            usource: "../../images/common/user.png"
            endImageVisible: false
        }
        ButtonItem {
            utext: "收藏到歌单"
            usource: "../../images/common/user.png"
        }
        ButtonItem {
            utext: "分享"
            usource: "../../images/common/user.png"
        }
        ButtonItem {
            utext: "复制链接"
            endImageVisible: false
            usource: "../../images/common/user.png"
        }
        ButtonItem {
            utext: "下载"
            usource: "../../images/common/user.png"
        }
    }
}
