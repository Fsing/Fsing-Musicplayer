#ifndef SONGBROKER_H
#define SONGBROKER_H
class RelationBroker;
class vector;
class Song;

class SongBroker
{
public:
    static SongBroker *Instance();
    void findByName();
    void selectAll();
    void getNext();
    void addSong();
    void deleteSong();

private:
    SongBroker();
    static SongBroker *m_instance;
    vector<Song*> _songs;
};

#endif // SONGBROKER_H
