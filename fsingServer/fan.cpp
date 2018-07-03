#include "fan.h"

Fan::Fan()
{

}

Fan::Fan(std::string name, std::string password, vector<std::shared_ptr<SongList> > createdSonglists)
    :m_name{name},m_password{password},_createdSongList{createdSonglists}
{

}

vector<std::shared_ptr<SongList> > Fan::getCollectedSongList()
{

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

