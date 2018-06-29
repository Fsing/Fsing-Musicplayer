#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

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
    Q_INVOKABLE void addCreateSongList(QString songlistName);
    //下载音乐
    Q_INVOKABLE QString songInformation(QString songSource);
    Q_INVOKABLE QString search(QString key);
    Q_INVOKABLE void fileTransfer(QString fileName);

//    void downloadMusic();

    //setting
    Q_INVOKABLE void setUserName(QString name){m_userName = name;}
    Q_INVOKABLE void setUserID(int id){m_userID = id;}
    Q_INVOKABLE void setLogining(bool b){m_logining = b;}
    Q_INVOKABLE void setResult(QString str){m_result = str;}

    //getting
    Q_INVOKABLE QString userName(){return m_userName;}
    Q_INVOKABLE int userID(){return m_userID;}
    Q_INVOKABLE bool logining(){return m_logining;}
    Q_INVOKABLE QString result(){return m_result;}


    //filetransfer
    void fileReceiver();
    void handle_write(const boost::system::error_code& error, size_t bytes_transferred);
    void receive_file_content();
    void handle_file(const boost::system::error_code& error);
    void handle_header(const boost::system::error_code& error);

signals:
    void userNameChanged();
    void userIDChanged();
    void loginingChanged();
    void resultChanged();

private:
    //用户信息
    QString m_userName;
    int m_userID;
    bool m_logining;

    QString m_result;
    QString m_songName;

    //for file transfer
    clock_t clock_;
    FILE *fp_;
    File_info file_info_;
    File_info::Size_type total_bytes_writen_;
    static const unsigned k_buffer_size = 1024 * 32;
    char buffer_[k_buffer_size];
};


#endif // CLIENT_H
