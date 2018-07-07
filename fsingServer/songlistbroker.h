#ifndef SONGLISTBROKER_H
#define SONGLISTBROKER_H
#include "ralationbroker.h"
#include "songlist.h"
#include <map>
#include <memory>
#include <string>
#include <vector>

class SongListBroker:public RalationBroker
{
public:
    static std::shared_ptr<SongListBroker> getInstance();
    std::shared_ptr<SongList> findSongList(std::string songId); //在缓存中查询
    std::shared_ptr<SongList> retrievalSongList(std::string songListID);
    std::map<std::string,std::shared_ptr<SongList>> findSongListsByUserName(std::string username);      //find user's createdSongLists
    std::shared_ptr<SongList> findSongListBySongListNameAndUserName(std::string songlistname,std::string username);     //根据歌单名and usename查找单个歌单
    std::map<std::string,std::shared_ptr<SongList>> findSongListsByCollectionRelation(std::string username);
    std::shared_ptr<SongList> findSongListsBySongListID(std::string songlistID);
private:
    SongListBroker();
    static std::shared_ptr<SongListBroker> _instance;
    std::map<std::string,std::shared_ptr<SongList>> _songLists;    //以用户名为键
};
#endif // SONGLISTBROKER_H
