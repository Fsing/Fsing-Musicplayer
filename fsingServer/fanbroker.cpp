#include "fanbroker.h"
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <memory>
#include "songlist.h"

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
    vector<std::shared_ptr<SongList>> songlists;

    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return NULL;
    }

    string name;
    string password;
    char sql[100];
    MYSQL_RES *result;
    MYSQL_ROW row;
    //查找账户信息
    std::sprintf(sql,"select * from Account WHERE name= '%s'",username.data());
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"fondUser select * from Account failed" << endl;
        return NULL;
    }else{
        result = mysql_store_result(&mysql);
        if(result){
            while(row = mysql_fetch_row(result)){
                if(string(row[1]) == username){
                    name = row[1];
                    password = row[2];
                }
            }
        }else{
            return NULL;
        }

        //查找用户歌单信息
        string songlistname = name + "CreatedSongList";
        std::sprintf(sql,"select * from %s",songlistname.data());
        size_t length =strlen(sql);
        int res = mysql_real_query(&mysql,sql,length);
        if(res != 0){
            cout <<"select * from " << songlistname << " faild " << endl;
        }else{
            result = mysql_store_result(&mysql);
            if(result){
                while(row = mysql_fetch_row(result)){
                    songlists.push_back(std::make_shared<SongList>(SongList(row[1],row[2],row[3])));
                }
            }
        }
        //往缓存中添加用户
        std::shared_ptr<Fan> ret = std::make_shared<Fan>(Fan(name,password,songlists));
        _fans.insert(std::make_pair(name,ret));
        return ret;
    }
    return NULL;
}


FanBroker::FanBroker()
{

}
