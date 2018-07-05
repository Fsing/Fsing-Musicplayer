#ifndef SONGLISTPROXY_H
#define SONGLISTPROXY_H
#include <string>

class SongListProxy
{
public:
    std::string songListInformation(std::string songId);
    std::string addSongList(std::string username, std::string songListName, std::string time);


};
#endif // SONGLISTPROXY_H
