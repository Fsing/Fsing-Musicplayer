#include "fanproxy.h"
#include <json/json.h>
#include <iostream>
#include "fanbroker.h"
#include <string>
#include <cstring>
#include <sstream>

using std::string;
using std::cout;        using std::endl;

std::string FanProxy::myLogin(std::string username, std::string password)
{
    Json::Value root;
    Json::Value arrayObj;
    root["type"] = "LOGIN";

    auto fanBroker = FanBroker::getInstance();
    auto res =fanBroker->findUser(username);

    if(res == NULL){
        root["loginSuccess"] = "NAME_INVALID";   //用户不存在
    }else{
        //用户存在
        root["userName"] = username;
        root["userPassword"] = password;
        if(password != res->getUserPw()){
            root["loginSuccess"] = "PW_INVALID";  //用户密码错误
        }else{
            root["loginSuccess"] = "SUCCESS";
            for(auto l:res->getCreatedSongList()){
                arrayObj.append(l->getName());
            }
        }
    }

    root["array"] = arrayObj;
    root.toStyledString();
    return root.toStyledString();
}

std::string FanProxy::myRegister(std::string username, std::string password)
{
    cout <<"enter Myregister" << endl;
    Json::Value root;
    root["type"] = "REGISTER";
    root["userName"] = username;
    root["userPassword"] = password;

    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "myRegister conect MYSQL failed!" << endl;
        root["registerSuccess"] = "FAILD";
    }

    //先查询是否有Account表，如果没有，则说明一个用户也没有，则可以直接创建Account,再往表中添加用户信息，完成注册
    //没有Account表,则创建Account表
    if(!hasTable("Account")){
        createAccountTable();
        if(insertUser(username,password)){
            root["registerSuccess"] = "SUCCESS";
        }
    }else{
        auto fanBroker = FanBroker::getInstance();
        auto res =fanBroker->findUser(username);

        //用户不存在，可以注册,往数据库中添加一个用户
        if(res == NULL){
            if(insertUser(username,password)){
                root["registerSuccess"] = "SUCCESS";
            }
            //创建用户原创歌单表
            if(!hasTable(username + "CreatedSongList"))
                createCreatedSongList(username + "CreatedSongList");
        }else{
            //用户存在，不可注册
            root["registerSuccess"] = "USER_VALID";
        }
    }

    root.toStyledString();
    return root.toStyledString();
}

//获得指定表最大id
int getMaxid(string tableName)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return 0;
    }

    char sql[100];
    std::sprintf(sql,"select max(id) from %s",tableName.data());
    auto length = strlen(sql);
    mysql_real_query(&mysql,sql,length);

    int maxid;
    MYSQL_RES *result;
    MYSQL_ROW row;
    result = mysql_store_result(&mysql);
    if(result){
        if(row = mysql_fetch_row(result)){
            string str = row[0];
            std::stringstream in(str);
            in >> maxid;
        }
    }
    return ++maxid;
}
bool FanProxy::insertUser(string username,string userpassword)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "insertUser conect MYSQL failed!" << endl;
        return false;
    }

    char sql[100];
    auto maxid = getMaxid("Account");
    std::sprintf(sql,"insert into Account(id,name,password) values('%d','%s','%s')",maxid,username.data(),userpassword.data());
    auto length = strlen(sql);
    if(!mysql_real_query(&mysql,sql,length)){
        cout <<"create user " << username << " success " << endl;
        return true;
    }
    return false;
}


std::string FanProxy::addCreateSongList(std::string username, std::string songListName, std::string time)
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

        //用户原创歌单表名
        auto tableName = username + "CreatedSongList";
        //往歌单表中插入一行歌单信息
        auto uname = username.data();
        auto lname = songListName.data();
        auto ctime = time.data();
        auto tableName1 = tableName.data();
        auto maxid = getMaxid(tableName);
        char sql[100];
        std::sprintf(sql,"insert into %s(id,username,listname,time) values('%d','%s','%s','%s')",tableName1,maxid,uname,lname,ctime);
        auto length = strlen(sql);
        if(!mysql_real_query(&mysql,sql,length)){
            cout <<"record create song list " << lname << " success " << endl;
            root["recordSuccess"] = "SUCCESS";
        }else {
            cout <<"record create song list " << lname << " false" << endl;
            root["recordSuccess"] = "INSERT_FALSE";
        }
    }else{
        cout <<"record create song list " << " false" << endl;
        root["recordSuccess"] = "INSERT_FALSE";
    }
    root.toStyledString();
    return root.toStyledString();
}

bool FanProxy::hasTable(std::string tableName)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "hasTable conect MYSQL failed!" << endl;
        return false;
    }

    //查找是否有tableName表
    MYSQL_RES *result;
    MYSQL_ROW row;
    char sql1[100];
    std::sprintf(sql1,"show tables;");
    auto length1 = std::strlen(sql1);
    mysql_real_query(&mysql,sql1,length1);
    result = mysql_store_result(&mysql);
    if(result){
        while(row = mysql_fetch_row(result)){
            if(row[0] == tableName){
                return true;
            }
        }
    }
    return false;
}

void FanProxy::createCreatedSongList(std::string songListName)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "createCreatedSongList conect MYSQL failed!" << endl;
        return;
    }

    auto name = songListName.data();
    char sql[100];
    std::sprintf(sql,"CREATE TABLE %s("
                     "id int NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                     "username char(20) not null,"
                     "listname char(20) not null,"
                     "time char(20) not null);",name);
    auto length = strlen(sql);
    if(!mysql_real_query(&mysql,sql,length)){
        cout <<"create table " <<songListName << "!" << endl;
    }
}

void FanProxy::createAccountTable()
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "createAccountTable conect MYSQL failed!" << endl;
        return;
    }

    //创建Account表
    string str{"CREATE TABLE Account("
               "id int NOT NULL AUTO_INCREMENT PRIMARY KEY,"
               "name char(20) not null,"
               "password char(20) not null);"};

    auto length = str.size();
    if(!mysql_real_query(&mysql,"CREATE TABLE Account("
                         "id int NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                         "name char(20) not null,"
                         "password char(20) not null);",length)){
        cout <<"create table Account!" << endl;
    }
}
