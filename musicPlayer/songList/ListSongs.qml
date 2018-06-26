import QtQuick 2.0
import QtQuick.Controls 1.4

TabView {
    width: 640
    height: 320
    Tab {
        title: "歌曲列表"
    }
    Tab {
        title: "评论"
        Rectangle {
            color: "blue"
        }
    }
    Tab {
        title: "收藏者"
        Rectangle {
            color: "green"
        }
    }
}
