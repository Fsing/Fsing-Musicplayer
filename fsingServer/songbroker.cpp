#include "songbroker.h"

std::shared_ptr<SongBroker> SongBroker::_instance = std::make_shared<SongBroker>(SongBroker());
SongBroker::SongBroker()
{

}
std::shared_ptr<SongBroker> SongBroker::getInstance()
{
    return _instance;
}
