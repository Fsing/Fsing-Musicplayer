#include "songlist.h"

void SongList::insertSong(std::shared_ptr<Song> ret)
{
    _songs.push_back(ret);
}

void SongList::setSongs(std::vector<std::shared_ptr<Song> > songs)
{
    _songs = songs;
}
