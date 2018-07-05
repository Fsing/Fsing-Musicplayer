#include "fanbroker.h"
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <memory>
#include "songlist.h"
#include "songlistbroker.h"

using std::cout;            using std::endl;
using std::string;          using std::vector;

std::shared_ptr<FanBroker> FanBroker::_instance = std::make_shared<FanBroker>(FanBroker());
std::shared_ptr<FanBroker> FanBroker::getInstance()
{
    return _instance;
}

std::shared_ptr<Fan> FanBroker::findUser(std::string username)
{
    cout << "enter findUser" << endl;
    if(_fans.find(username) != _fans.end()){
        return _fans[username];
    }else{
        return retrievalUser(username);
    }
}

std::shared_ptr<Fan> FanBroker::retrievalUser(std::string username)
{
    cout << "enter retrievalUser" << endl;

    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "retrievalUser conect MYSQL failed!" << endl;
        return nullptr;
    }

    //    string id;
    string name;
    string password;
    string label;
    string sex;
    string birthday;
    string address;
    string icon;
    //    bool idVaild;
    char sql[512];
    MYSQL_RES *result;
    MYSQL_ROW row;
    //查找账户信息
    std::sprintf(sql,"select * from Account WHERE name= '%s'",username.data());
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"retrievalUser select * from Account failed" << endl;
        return nullptr;
    }else{
        result = mysql_store_result(&mysql);
        if(result){
            if(row = mysql_fetch_row(result)){
                if(string(row[1]) == username){
                    //                    id = row[0];
                    name = row[1];
                    password = row[2];
//                    label = row[3];
//                    sex = row[4];
//                    birthday = row[5];
//                    address = row[6];
//                    icon = row[7];
                }
            }else{
                return nullptr;
            }
        }

        //查找用户created歌单信息
        auto songlistBroker = SongListBroker::getInstance();
        auto createdSongLists = songlistBroker->findSongListsByUserName(username);

        //查找用户collected歌单信息
        vector<std::shared_ptr<SongList>> collectedSongLists = songlistBroker->findSongListsByCollectionRelation(username);

        //往缓存中添加用户
        std::shared_ptr<Fan> ret = std::make_shared<Fan>(Fan(name,password,icon,createdSongLists,collectedSongLists));
        _fans.insert(std::make_pair(username,ret));
        return ret;
    }
    return nullptr;
}


FanBroker::FanBroker()
{

}
