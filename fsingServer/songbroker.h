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
    static std::shared_ptr<SongBroker> getInstance();
private:
    SongBroker();
   static std::shared_ptr<SongBroker> _instance;
   std::map<std::string,std::shared_ptr<Song>> _songs;
};

#endif // SONGBROKER_H
