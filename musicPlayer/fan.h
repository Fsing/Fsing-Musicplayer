#ifndef FAN_H
#define FAN_H

/*
 * 用户登录时，服务器会返回用户所有的信息：基本信息、收藏歌单（只有歌单基本信息）、创建的歌单（只有歌单基本信息）、关注用户（只有用户基本信息）、粉丝只有（用户基本信息）
 */
#include <QObject>
#include "songlist.h"
#include <QMap>

using std::string;      using std::vector;
using std::map;

class Fan:QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(QString sex READ sex WRITE setSex NOTIFY sexChanged)
    Q_PROPERTY(QString birthday READ birthday WRITE setBirthday NOTIFY birthdayChanged)
    Q_PROPERTY(QString address READ address WRITE setAddress NOTIFY addressChanged)
    Q_PROPERTY(QString icon READ icon WRITE setIcon NOTIFY iconChanged)
public:
    //构造函数
    Fan(){}
    Fan(QString name,QString password,QString label,QString sex,QString birthday,QString address,QString icon);

    //methods
    int attentionUserCount();
    int fanUserCount();
    int createdSongListCount();
    int collectedSongListCount();
    //getting
    QString username();
    QString password();
    QString label();
    QString sex();
    QString birthday();
    QString address();
    QString icon();
    //getting
    QMap<QString, QList<QString> > createdSongLists();
    QMap<QString, QList<QString>> collectedSongLists();
    QMap<QString, QList<QString> > attentedUsers();
    QMap<QString, QList<QString> > fanUsers();

    //setting
    void setUsername(QString username);
    void setPassword(QString password);
    void setLabel(QString label);
    void setSex(QString sex);
    void setBirthday(QString birthday);
    void setAddress(QString address);
    void setIcon(QString icon);

    //adding
    void addCreatedSongList(QString key,QList<QString> s){_createdSongList.insert(key,s);}
    void addCollectedSongLists(QString key,QList<QString> s){_collectedSongList.insert(key,s);}
    void addAttentedUsers(QString key,QList<QString> s){_attentedUsers.insert(key,s);}
    void addFanUsers(QString key,QList<QString> s){_fanUsers.insert(key,s);}

    //deleting
//    void deleteAttentedUsers(Fan attentedUsers);
//    void deleteFanUsers(Fan fanUsers);
//    void deleteCollectedSongLists(SongList collectedSongList);
//    void deleteCreatedSongLists(SongList createdSongList);

signals:
    void usernameChanged();
    void passwordChanged();
    void labelChanged();
    void sexChanged();
    void birthdayChanged();
    void addressChanged();
    void iconChanged();
private:
    QString m_name;         //用户名
    QString m_password;     //用户密码
    QString m_label;        //用户标签
    QString m_sex;          //性别
    QString m_birthday;     //生日
    QString m_address;      //地址
    QString m_icon;         //头像，保存路径
//    bool m_vaild;               //状态变量，用来标志歌曲是否违法，是否可用

    QMap<QString,QList<QString>> _collectedSongList;              //已收藏歌单
    QMap<QString,QList<QString>> _createdSongList;                //创建歌单
    QMap<QString,QList<QString>> _attentedUsers;                  //关注的用户
    QMap<QString,QList<QString>> _fanUsers;                       //粉丝
};
#endif // FAN_H
