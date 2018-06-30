#include "songlistbroker.h"

SongListBroker *SongListBroker::_instance = new SongListBroker();

SongListBroker::SongListBroker()
{

}
SongListBroker *SongListBroker::getInstance()
{
    return _instance;
}
