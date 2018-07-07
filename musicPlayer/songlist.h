#ifndef SONGLIST_H
#define SONGLIST_H

#include <QObject>

class SongList:QObject
{
    Q_OBJECT
public:
    SongList(){}
    SongList(int id,QString name,QString author, QString createTime,QString label,
             QString info,QString icon,int collectionQuantity,
             int clickQuantity,int shareQuantity)
        :m_id{id},m_name{name},m_author{author},m_createTime{createTime},m_label{label},
          m_info{info},m_icon{icon},m_collectionQuantity{collectionQuantity},
          m_clickQuantity{clickQuantity},m_shareQuantity{shareQuantity}{}
//    SongList():m_id{0},m_name{""},m_author{""},m_createTime{""},m_label{""},m_info{""},m_icon{""},m_collectionQuantity{0},m_clickQuantity{0},m_shareQuantity{0}{}

private:
    int m_id;                       //歌单ID，歌单的关键字，标识符
    QString m_name;             //歌单名
    QString m_author;           //歌单创建者
    QString m_createTime;       //创建时间

    //double m_size;                  //大小
    QString m_label;            //标签
    QString m_info;             //简介
    QString m_icon;             //歌单头像路径
    //std::string m_comment;          //评论
    int m_collectionQuantity;       //收藏量
    int m_clickQuantity;            //点击量
    int m_shareQuantity;            //分享量
//    std::map<std::string,std::shared_ptr<Fan>> _collectionUsers;        //收藏歌单的所有用户
//    std::map<std::string,std::shared_ptr<Song>> _songs;                 //歌单中的歌
};
#endif // SONGLIST_H
