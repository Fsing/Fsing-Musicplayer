#include "songbroker.h"

SongBroker *SongBroker::_instance = new SongBroker();

SongBroker::SongBroker()
{

}
SongBroker *SongBroker::getInstance()
{
    return _instance;
}
