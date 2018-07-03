#include "songlist.h"


SongList::SongList()
{

}

SongList::SongList(std::string author, std::string songlistname, std::string createTime)
    :m_author{author},m_name{songlistname},m_createTime{createTime}
{

}

std::string SongList::getName()
{
    return m_name;
}
