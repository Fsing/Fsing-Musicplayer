#ifndef SONGBROKER_H
#define SONGBROKER_H
#include "ralationbroker.h"
#include "song.h"
#include<map>
#include <memory>
#include <string>

class SongBroker:public RalationBroker
{
public:
    static SongBroker *getInstance();
//    void findByName();
//    void selectAll();
//    void getNext();
//    void addSong();
//    void deleteSong();
private:
     SongBroker();
    static SongBroker *_instance;
    std::map<std::string,std::shared_ptr<Song>> _songs;
};

#endif // SONGBROKER_H
