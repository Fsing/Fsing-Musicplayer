#include "songlistbroker.h"

SongListBroker::SongListBroker()
{

}

SongListBroker *SongListBroker::Instance()
{
    if (m_instance == nullptr)
        m_instance = new SongListBroker();
    return m_instance;
}
