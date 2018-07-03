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

private:
    SongListBroker();
    static std::shared_ptr<SongListBroker> _instance;
    std::multimap<std::string,SongList> _userSongLists;    //以用户名为键
    std::multimap<std::string,SongList> _SystemSongLists;  //系统歌单，以歌单名为键
};
#endif // SONGLISTBROKER_H