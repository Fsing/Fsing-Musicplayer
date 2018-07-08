#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
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
    Q_INVOKABLE void fileTransfer(QString fileName);
    Q_INVOKABLE void songList(QString songListId);//get songlist infomation
    Q_INVOKABLE void interface(QString interfaceName);//get songlist infomation

    //关注、粉丝个数、用户名
    Q_INVOKABLE int attentionUserCount(){return _fan.attentionUserCount();}
    Q_INVOKABLE int fanUserCount(){return _fan.fanUserCount();}
    Q_INVOKABLE int createdSongListCount(){return _fan.createdSongListCount();}
    Q_INVOKABLE int collectedSongListCount(){return _fan.collectedSongListCount();}


    //setting
    Q_INVOKABLE void setUserName(QString name){m_userName = name;}
    Q_INVOKABLE void setUserID(int id){m_userID = id;}
    Q_INVOKABLE void setLogining(bool b){m_logining = b;}
    Q_INVOKABLE void setResult(QString str){m_result = str;}

    //getting
    Q_INVOKABLE QString userName(){return m_userName;}
    Q_INVOKABLE QString getSongName(){return m_songName;}
    Q_INVOKABLE int userID(){return m_userID;}
    Q_INVOKABLE bool logining(){return m_logining;}
    Q_INVOKABLE QString result(){return m_result;}
    //
    Q_INVOKABLE QList<QString> getinterface() const{return m_interface;}
    Q_INVOKABLE QList<QString> getSongListInformation(QString songListId);
    Q_INVOKABLE QList<QString> getSongListSongs(QString songListId);
    Q_INVOKABLE int getSongListCount() const{return m_songListCount;}

    Q_INVOKABLE QList<QString> getSongInformation() const{return m_songInformation;}
    Q_INVOKABLE QList<QString> createdSongLists() const{return _songlistNames;}


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
    void fileReceiver();
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

private:
    //cache pool
    std::map<int,std::shared_ptr<SongList>> m_songlistsMap;
    std::map<int,std::shared_ptr<Song>> m_songsMap;


    //用户信息
    QString m_userName;
    int m_userID;
    bool m_logining;
    int i;

    //用户代理
//    FanProxy _fanProxy;

    QString m_result;
    QString m_songName;

    Fan _fan;
    QList<QString> m_currentPlayListSong;//playlist song id

    //用户原创歌单名
    QList<QString> _songlistNames;
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
