#ifndef SONG_H
#define SONG_H

#include <string>

class Song
{
public:
    Song();

private:
    std::string m_name;         //歌曲名
    std::string m_singer;       //歌手
    std::string m_album;        //专辑
    int m_duration;             //毫秒
    double m_size;              //文件大小
    std::string m_comment;      //评论
    int m_playQuantity;         //歌曲播放量
    int m_downloadQuantity;     //下载量
    int m_shareQuantity;        //分享量
};
#endif // SONG_H
