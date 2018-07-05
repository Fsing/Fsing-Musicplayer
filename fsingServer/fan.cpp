#include "fan.h"

Fan::Fan()
{

}

Fan::Fan(std::string name, std::string password, std::string icon, vector<std::shared_ptr<SongList> > createdSonglists, vector<std::shared_ptr<SongList> > collectedSongList)
    :m_name{name},m_password{password},_createdSongList{createdSonglists},_collectedSongList{collectedSongList}
{

}

vector<std::shared_ptr<SongList> > Fan::getCollectedSongList()
{
    return _collectedSongList;
}

vector<std::shared_ptr<SongList>> Fan::getCreatedSongList()
{
    return _createdSongList;
}

std::string Fan::getUserName()
{
    return m_name;

}

std::string Fan::getUserPw()
{
    return m_password;
}

