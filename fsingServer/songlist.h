#ifndef SONGLIST_H
#define SONGLIST_H

#include <string>
#include <memory>
#include <map>
#include "user.h"
#include "song.h"

class SongList
{
public:
    SongList();

private:
    std::string m_name;             //歌单名
    double m_size;                  //大小
    std::string m_label;            //标签
    std::string m_info;             //简介
    std::string m_icon;             //歌单头像路径
    std::string m_author;           //歌单创建者
    std::string m_createTime;       //创建时间
    std::string m_comment;          //评论
    int m_collectionQuantity;       //收藏量
    int m_clickQuantity;            //点击量
    int m_shareQuantity;            //分享量
    std::map<std::string,std::shared_ptr<User>> _collectionUsers;        //收藏歌单的所有用户
    std::map<std::string,std::shared_ptr<Song>> _songs;                 //歌单中的歌
};
#endif // SONGLIST_H
