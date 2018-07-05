#include "songbroker.h"
#include <string.h>
#include <iostream>
#include "song.h"

std::shared_ptr<SongBroker> SongBroker::_instance = std::make_shared<SongBroker>(SongBroker());
SongBroker::SongBroker()
{
}
std::shared_ptr<Song> SongBroker::findSong(std::string id)
{
    if(_songs.find(id) != _songs.end()){
        std::cout << "find previous data"<< id << std::endl;
        return _songs[id];
    }else{
        return retrievalSong(id);
    }
}

std::shared_ptr<Song> SongBroker::retrievalSong(std::string id)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        std::cout << "findUser conect MYSQL failed!" << std::endl;
        return nullptr;
    }

    char sql[512];
    auto source = id.data();

    std::sprintf(sql,"select * from Song WHERE id = '%s'",source);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        std::cout <<"retrievalSong: select * from Song failed" << std::endl;
        return nullptr;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        result = mysql_store_result(&mysql);
        if(result){
            while(row = mysql_fetch_row(result)){
                //往缓存中添加用户
                std::shared_ptr<Song> ret = std::make_shared<Song>(Song(atoi(row[0]),row[1],row[2],
                        row[3],row[4],atoi(row[5]),atoi(row[6]),atoi(row[7])));
                _songs.insert(std::make_pair(row[0],ret));
                return ret;
            }
        }
    }
}

std::vector<std::shared_ptr<Song> > SongBroker::findSongsBySongListRelation(std::string songlistID)
{
    std::vector<std::shared_ptr<Song>> ret;
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        std::cout << "findSongsBySongListRelation: conect MYSQL failed!" << std::endl;
        return ret;
    }

    char sql[512];
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::sprintf(sql,"select * from SongListRelation WHERE songlistID = '%s'",songlistID.data());
    auto length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        std::cout <<"findSongsBySongListRelation: select * from Song failed" << std::endl;
        return ret;
    }else{
        result = mysql_store_result(&mysql);
        if(result){
            while(row = mysql_fetch_row(result)){
                //查找歌单中的所有歌曲,并push进vector
                ret.push_back(std::make_shared<Song>(Song(atoi(row[0]),row[1],row[2],row[3],row[4],atoi(row[5]),atoi(row[6]),atoi(row[7]))));
            }
        }
    }
    return ret;
}
std::shared_ptr<SongBroker> SongBroker::getInstance()
{
    return _instance;
}
