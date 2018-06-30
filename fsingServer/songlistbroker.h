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
    static SongListBroker *getInstance();
//    void findByAuthor();
//    void findByName();
//    void selectAll();
//    void getNext();
//    void addSongList();
//    void deleteSongList();
private:
    SongListBroker();
    static SongListBroker *_instance;
    std::map<std::string,std::shared_ptr<SongList>> _songLists;
};
#endif // SONGLISTBROKER_H
