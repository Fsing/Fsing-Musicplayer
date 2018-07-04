#ifndef SONGLISTBROKER_H
#define SONGLISTBROKER_H
#include "ralationbroker.h"
#include "songlist.h"
#include <map>
#include <memory>
#include <string>

class SongListBroker:public RalationBroker
{
public:
    static std::shared_ptr<SongListBroker> getInstance();
    std::shared_ptr<SongList> findSongList(std::string songId); //在缓存中查询
    std::shared_ptr<SongList> retrievalSongList(std::string songId);
private:
    SongListBroker();
    static std::shared_ptr<SongListBroker> _instance;
    std::map<std::string,std::shared_ptr<SongList>> _userSongLists;    //以用户名为键
    std::map<std::string,std::shared_ptr<SongList>> _systemSongList;  //系统歌单，以歌单名为键
};
#endif // SONGLISTBROKER_H
