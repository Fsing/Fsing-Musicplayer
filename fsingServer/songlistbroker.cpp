#include "songlistbroker.h"

std::shared_ptr<SongListBroker> SongListBroker::_instance = std::make_shared<SongListBroker>(SongListBroker());
SongListBroker::SongListBroker()
{

}
std::shared_ptr<SongListBroker> SongListBroker::getInstance()
{
    return _instance;
}

