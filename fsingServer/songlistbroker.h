#ifndef SONGLISTBROKER_H
#define SONGLISTBROKER_H
class RelationBroker;
class vector;
class SongList;

class SongListBroker
{
public:
    static SongListBroker *Instance();
    void findByAuthor();
    void findByName();
    void selectAll();
    void getNext();
    void addSongList();
    void deleteSongList();


private:
    SongListBroker();
    static SongListBroker *m_instance;
    vector<SongList*> _songLists;
};

#endif // SONGLISTBROKER_H
