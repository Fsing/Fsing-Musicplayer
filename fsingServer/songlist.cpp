#include "songlist.h"

void SongList::insertSong(std::string songlistID,std::shared_ptr<Song> ret)
{
    _songs[songlistID] = ret;
}

void SongList::setSongs(std::map<std::string, std::shared_ptr<Song> > songs)
{
    _songs = songs;
}
