#include "fanbroker.h"

FanBroker::FanBroker()
{

}

FanBroker *FanBroker::Instance()
{
    if (m_instance == nullptr)
        m_instance = new FanBroker();
    return m_instance;
}
