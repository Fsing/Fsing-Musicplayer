#include "songlistbroker.h"
#include <iostream>
#include "string.h"
#include <string>

std::shared_ptr<SongListBroker> SongListBroker::_instance = std::make_shared<SongListBroker>(SongListBroker());
SongListBroker::SongListBroker()
{

}
std::shared_ptr<SongListBroker> SongListBroker::getInstance()
{
    return _instance;
}

std::shared_ptr<SongList> SongListBroker::findSongList(std::string songId)
{
    if(_systemSongList.find(songId) != _systemSongList.end()){
        std::cout << "find previous songlist "<< songId << std::endl;
        return _systemSongList[songId];
    }else{
        return retrievalSongList(songId);
    }
}

std::shared_ptr<SongList> SongListBroker::retrievalSongList(std::string songId)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        std::cout << " conect MYSQL failed!" << std::endl;
        return nullptr;
    }
    MYSQL mysqlSong;
    mysql_init(&mysqlSong);
    if(!mysql_real_connect(&mysqlSong,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        std::cout << " conect MYSQL failed512!" << std::endl;
    }

    char sql[100];
    char sqlSong[100];
    auto source = songId.data();
    auto sourceSong = (songId + "Song").data();
    std::sprintf(sql,"select * from SongList WHERE id = '%s'",source);
    std::sprintf(sqlSong,"select * from %s",sourceSong);

    size_t length =strlen(sql);
    size_t lengthSong =strlen(sqlSong);

    int res = mysql_real_query(&mysql,sql,length);
    int resSong = mysql_real_query(&mysqlSong,sqlSong,lengthSong);

    if(res != 0){
        std::cout <<" select * from SongList failed" << std::endl;
        return nullptr;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        result = mysql_store_result(&mysql);

        row = mysql_fetch_row(result);
        std::shared_ptr<SongList> ret = std::make_shared<SongList>(SongList(atoi(row[0]),row[1],row[2],
                row[3],row[4],row[5],row[6],atoi(row[7]),atoi(row[8]),atoi(row[9])));

        _systemSongList.insert(std::make_pair(row[0],ret));
        if(resSong != 0){
            std::cout <<" select * from SongListSong failed" << std::endl;
        }else {
            MYSQL_RES *resultSong;
            MYSQL_ROW rowSong;
            resultSong = mysql_store_result(&mysqlSong);
            if(resultSong){
                while(rowSong = mysql_fetch_row(resultSong)){
                    std::shared_ptr<Song> retSong = std::make_shared<Song>(Song(rowSong[0],rowSong[1],rowSong[2],
                            rowSong[3],rowSong[4],atoi(rowSong[5]),atoi(rowSong[6]),atoi(rowSong[7])));
                    ret->insertSong(rowSong[0],retSong);
                }
            }
        }
            return ret;
    }

}
