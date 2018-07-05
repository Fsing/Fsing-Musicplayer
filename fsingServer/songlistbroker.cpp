#include "songlistbroker.h"
#include <iostream>
#include "string.h"
#include <string>

using std::cout;
using std::endl;
using std::vector;

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
std::shared_ptr<SongList> SongListBroker::findSongListBySongListNameAndUserName(std::string songlistname,std::string username)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "retrievalUser conect MYSQL failed!" << endl;
        return NULL;
    }

    std::shared_ptr<SongList> ret;
    char sql[512];
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::sprintf(sql,"select * from SongList where name='%s' and author='%s'",songlistname.data(),username.data());
    size_t length = strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"findSongListBySongListNameAndUserName: select * from SongList faild " << endl;
    }else{
        result = mysql_store_result(&mysql);
        if(result){
            if(row = mysql_fetch_row(result)){
                ret = std::make_shared<SongList>(SongList(atoi(row[0]),row[1],row[2],
                        row[3],row[4],row[5],row[6],atoi(row[7]),atoi(row[8]),atoi(row[9])));
            }
        }
    }

    return ret;
}

std::vector<std::shared_ptr<SongList>> SongListBroker::findSongListsByCollectionRelation(std::string username)
{
    vector<std::shared_ptr<SongList>> collectedSongLists;
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findSongListsByCollectionRelation: conect MYSQL failed!" << endl;
        return collectedSongLists;
    }

    char sql[512];
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::sprintf(sql,"select * from CollectionRelation where collecteUser='%s'",username.data());
    size_t length = strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"findSongListsByCollectionRelation:select * from CollectionRelation faild " << endl;
    }else{
        result = mysql_store_result(&mysql);
        if(result){
            while(row = mysql_fetch_row(result)){
                collectedSongLists.push_back(findSongListBySongListNameAndUserName(std::string(row[0]),username));
            }
        }
    }
    return collectedSongLists;
}

std::vector<std::shared_ptr<SongList> > SongListBroker::findSongListsByUserName(std::string username)
{
    vector<std::shared_ptr<SongList>> songlists;
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "retrievalUser conect MYSQL failed!" << endl;
        return songlists;
    }

    char sql[512];
    MYSQL_RES *result;
    MYSQL_ROW row;
    std::sprintf(sql,"select * from SongList where author='%s'",username.data());
    size_t length = strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"findSongListsByUserName:select * from SongList faild " << endl;
    }else{
        result = mysql_store_result(&mysql);
        if(result){
            while(row = mysql_fetch_row(result)){
                songlists.push_back(std::make_shared<SongList>(SongList(atoi(row[0]),row[1],row[2],
                        row[3],row[4],row[5],row[6],atoi(row[7]),atoi(row[8]),atoi(row[9]))));
             }
         }
     }

    return songlists;
 }

