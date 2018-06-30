#include "fanbroker.h"

FanBroker *FanBroker::_instance = new FanBroker();
FanBroker *FanBroker::getInstance()
{
    return _instance;
}

FanBroker::FanBroker()
{

}
