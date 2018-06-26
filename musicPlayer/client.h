#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <boost/asio.hpp>

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
    //异步连接run
//    void run_service();
};


#endif // CLIENT_H
