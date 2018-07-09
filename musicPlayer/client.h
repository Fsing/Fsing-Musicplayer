#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <QMap>
#include <string>
#include "fan.h"
#include "songlist.h"
#include "song.h"

struct File_info {
    typedef unsigned long long Size_type;
    Size_type filesize;
    size_t filename_size;
    File_info() : filesize(0), filename_size(0) {}
};


class Client:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(int userID READ userID WRITE setUserID NOTIFY userIDChanged)
    Q_PROPERTY(bool logining READ logining WRITE setLogining NOTIFY loginingChanged)
    Q_PROPERTY(QString result READ result WRITE setResult NOTIFY resultChanged)
    Q_PROPERTY(int attentionUserCount READ attentionUserCount WRITE setAttentionUserCount NOTIFY attentionUserCountChanged)
    Q_PROPERTY(int fanUserCount READ fanUserCount WRITE setFanUserCount NOTIFY fanUserCountChanged)
    Q_PROPERTY(int createdSongListCount READ createdSongListCount WRITE setCreatedSongListCount NOTIFY createdSongListCountChanged)
    Q_PROPERTY(int collecedSongListCount READ collecedSongListCount WRITE setCollecedSongListCount NOTIFY collecedSongListCountChanged)
    Q_PROPERTY(QString userIcon READ userIcon WRITE setUserIcon NOTIFY userIconChanged)
public:
    //构造函数
    Client();

    //连接服务器
    Q_INVOKABLE void myConnect();
    //自动登录，查找本地配置文件是否有登录信息
    Q_INVOKABLE void readUserConfig();
    //登录账户,服务器数据库查找用户信息
    Q_INVOKABLE void myLogin(QString username,QString userpw);
    //注册账户，服务器数据库查找，并插入信息
    Q_INVOKABLE void myRegister(QString username,QString userpw);
    //创建歌单
    Q_INVOKABLE void addCreateSongList(QString username, QString songlistName, QString time);
    //下载音乐
    Q_INVOKABLE QString songInformation(QString songId);
    Q_INVOKABLE QString search(QString key);
    //请求文件
    Q_INVOKABLE void fileTransfer(QString fileName);
    Q_INVOKABLE void songList(QString songListId);//get songlist infomation
    Q_INVOKABLE void interface(QString interfaceName);//get songlist infomation


    //setting
    Q_INVOKABLE void setUserName(QString name){m_userName = name;}
    Q_INVOKABLE void setUserID(int id){m_userID = id;}
    Q_INVOKABLE void setLogining(bool b){m_logining = b;}
    Q_INVOKABLE void setResult(QString str){m_result = str;}

    //setting 关注用户数、粉丝个数、用户名，创建歌单数、收藏歌单数
    Q_INVOKABLE void setAttentionUserCount(int i){m_attentedUserCount = i;}
    Q_INVOKABLE void setFanUserCount(int i){m_fanUserCount = i;}
    Q_INVOKABLE void setCreatedSongListCount(int i){m_CreatedSongListCount = i;}
    Q_INVOKABLE void setCollecedSongListCount(int i){m_collectedSongListCount = i;}

    //setting 更改用户头像
    Q_INVOKABLE void setUserIcon(QString icon){m_icon = icon;}

    //getting 用户信息
    Q_INVOKABLE QString userName(){return m_userName;}
    Q_INVOKABLE QString getSongName(){return m_songName;}
    Q_INVOKABLE int userID(){return m_userID;}
    Q_INVOKABLE bool logining(){return m_logining;}
    Q_INVOKABLE QString userIcon(){return m_icon;}

    Q_INVOKABLE QString result(){return m_result;}
    //
    Q_INVOKABLE QList<QString> getinterface() const{return m_interface;}
    Q_INVOKABLE QList<QString> getSongListInformation(QString songListId);
    Q_INVOKABLE QList<QString> getSongListSongs(QString songListId);
    Q_INVOKABLE int getSongListCount() const{return m_songListCount;}

    Q_INVOKABLE QList<QString> getSongInformation() const{return m_songInformation;}

    //创建歌单的名字集合
    Q_INVOKABLE QList<QString> createdSongLists() const{return _songlistNames;}
    //收藏歌单名字集合
    Q_INVOKABLE QList<QString> collectedSongLists() const{return _collectedSongListNames;}
    //用户关注用户名字+icon集合
    Q_INVOKABLE QList<QString> attentedUsers();
    //用户粉丝信息集合
    Q_INVOKABLE QList<QString> fanUsers();

    //getting 关注用户数、粉丝个数、用户名，创建歌单数、收藏歌单数
    Q_INVOKABLE int createdSongListCount() const{return m_CreatedSongListCount;}
    Q_INVOKABLE int collecedSongListCount() const{return m_collectedSongListCount;}
    Q_INVOKABLE int attentionUserCount() const {return m_attentedUserCount;}
    Q_INVOKABLE int fanUserCount() const{return m_fanUserCount;}


    //check the song id is added to the playlist
    Q_INVOKABLE bool currentPlayListSong(const QString id) {
        if(m_currentPlayListSong.contains(id))
            return true;
        else {
                auto song = m_songsMap[id.toInt()];
                  auto l =song->getName();
                l = l.substr(0,sizeof(l)-4) + ".lrc";
                fileTransfer(QString::fromStdString(l));
                m_currentPlayListSong.append(id);
            return false;
        }
}

    //filetransfer
    //接收文件
    void fileReceiver();
    //传文件调用函数
    void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
    void receive_file_content(std::string fileName);
    void handle_file(const boost::system::error_code& error);
    void handle_header(const boost::system::error_code& error);


signals:
    void userNameChanged();
    void userIDChanged();
    void loginingChanged();
    void resultChanged();
    void createdSongListsChanged();
    void attentionUserCountChanged();
    void fanUserCountChanged();
    void createdSongListCountChanged();
    void collecedSongListCountChanged();
    void userIconChanged();
private:
    //cache pool
    std::map<int,std::shared_ptr<SongList>> m_songlistsMap;
    std::map<int,std::shared_ptr<Song>> m_songsMap;


    //用户信息
    QString m_userName;
    int m_userID;
    QString m_icon;
    bool m_logining = false;
    int i;

    //用户代理
//    FanProxy _fanProxy;

    QString m_result;
    QString m_songName;

    //用户信息
    Fan _fan;
    int m_CreatedSongListCount = 0;
    int m_collectedSongListCount = 0;
    int m_fanUserCount = 0;
    int m_attentedUserCount = 0;

    QList<QString> m_currentPlayListSong;//playlist song id

    //用户原创歌单名
    QList<QString> _songlistNames;
    //用户收藏歌单名
    QList<QString> _collectedSongListNames;

    QList<QString> m_interface;
    //songlist infomation
    QList<QString> m_songListInformation;
    QList<QString> m_songList;
    int m_songListCount;
    QList<QString> m_songInformation;

    //for file transfer
    clock_t clock_;
    FILE *fp_;
    File_info file_info_;
    File_info::Size_type total_bytes_writen_;
    static const unsigned k_buffer_size = 1024 * 32;
    char buffer_[k_buffer_size];
};


#endif // CLIENT_H
