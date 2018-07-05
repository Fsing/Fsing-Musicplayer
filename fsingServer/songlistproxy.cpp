#include "songlistproxy.h"
#include "songlistbroker.h"
#include "songbroker.h"
#include "songproxy.h"
#include "json/json.h"
#include "fanproxy.h"
#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

std::string SongListProxy::songListInformation(std::string songId){
    auto songListBroker = SongListBroker::getInstance();
    auto res =songListBroker->findSongList(songId);

    Json::Value root;
    Json::Value arryObj;
    root["type"] = "SONGLIST";
    if(res == NULL){
        root["hasData"] = "no";
        return root.toStyledString();
    }else{
        root["id"] = res->getId();
        root["name"] = res->getName();
        root["author"] = res->getAuthor();
        root["createTime"] = res->getCreateTime();
        root["label"] = res->getLabel();
        root["info"] = res->getInfo();
        root["icon"] =res->getIcon();
        root["collectionQuantity"] = res->getCollectionQuantity();
        root["clickQuantity"] = res->getClickQuantity();
        root["shareQuantity"] = res->getShareQuantity();

        auto map = res->getSongs();
        for(auto iter = map.begin(); iter != map.end(); iter++) {
             Json::Value item;
             item["id"] = iter->second->getId();
             item["name"] = iter->second->getName();
             item["source"] = iter->second->getSource();
             item["singer"] = iter->second->getSinger();
             item["album"] = iter->second->getAlbum();
             item["playQuantity"] = iter->second->getPlayQuantity();
             item["downloadQuantity"] = iter->second->getDownloadQuantity();
             item["shareQuantity"] = iter->second->getShareQuantity();
             arryObj.append(item);
         }
        root["array"] = arryObj;
        return root.toStyledString();
    }
}
std::string SongListProxy::addSongList(std::string username, std::string songListName, std::string time)
{
    Json::Value root;
    root["type"] = "CREATESONGLIST";
    root["username"] = username;
    root["songListName"] = songListName;   //歌单名
    root["createTime"] = time;

    if(username.size()){
        //记录创建歌单成功返回SUCCESS,反之返回FAILD
        MYSQL mysql;
        mysql_init(&mysql);
        if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
            cout << "addCreateSongList conect MYSQL failed!" << endl;
            root["recordSuccess"] = "FAILD";
        }

        //验证是否已经有重复的歌单名，有则不可创建
        char sql[512];
        MYSQL_RES *result;
        MYSQL_ROW row;
        std::sprintf(sql,"select * from SongList where name='%s' and author='%s'",songListName.data(),username.data());
        if(!mysql_real_query(&mysql,sql,strlen(sql))){
            cout <<"addSongList: select * from SongList success!" << endl;
        }else{
            result = mysql_store_result(&mysql);
            if(result){
                while(row = mysql_fetch_row(result)){
                    root["recordSuccess"] = "NAME_INVAILD";
                    root.toStyledString();
                    return root.toStyledString();
                }
            }
        }

        //歌单名可用，插入一行歌单信息
        MYSQL mysql1;
        mysql_init(&mysql1);
        if(!mysql_real_connect(&mysql1,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
            cout << "addCreateSongList conect MYSQL failed!" << endl;
            root["recordSuccess"] = "FAILD";
        }
        auto uname = username.data();
        auto lname = songListName.data();
        auto ctime = time.data();
//        char sql1[512];
        std::shared_ptr<FanProxy> fanProxy;
        auto maxid = fanProxy->getMaxid("SongList");
        std::sprintf(sql,"insert into SongList(id,name,author,createTime,label,info,icon,collectionQuantity,clickQuantity,shareQuantity) values('%d','%s','%s','%s','0','0','0',0,0,0)",maxid,lname,uname,ctime);
        auto length = strlen(sql);
        cout << sql << endl;
        if(!mysql_real_query(&mysql1,sql,length)){
            cout <<"addSongList:insert into SongList: " << songListName << " success!" << endl;
            root["recordSuccess"] = "SUCCESS";
        }else {
            cout <<"record create song list " << lname << " false" << endl;
            root["recordSuccess"] = "INSERT_FALSE";
        }
    }else{
        cout <<"addSongList:insert into SongList: " << songListName << " faild!" << endl;
        root["recordSuccess"] = "INSERT_FALSE";
    }
    root.toStyledString();
    return root.toStyledString();
}
