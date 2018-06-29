#include "songbroker.h"

SongBroker::SongBroker()
{

}

SongBroker *SongBroker::Instance()
{
    if(m_instance == nullptr)
        m_instance = new SongBroker();
    return m_instance;
}
