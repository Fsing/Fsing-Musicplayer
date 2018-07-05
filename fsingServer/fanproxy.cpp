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
    Json::Value arrayObj1;
    Json::Value arrayObj2;
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
                arrayObj1.append(l->getName());
            }
            for(auto l:res->getCollectedSongList()){
                arrayObj2.append(l->getName());
            }
        }
    }

    root["array"] = arrayObj1;
    root["collectedArray"] = arrayObj2;
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
        root.toStyledString();
        return root.toStyledString();
    }

    //先查询是否有Account表，如果没有，则说明一个用户也没有，则可以直接创建Account,再往表中添加用户信息，完成注册
    //没有Account表,则创建Account表
    if(!hasTable("Account")){
        if(createAccountTable()){
            root["registerSuccess"] = "FAILD";
            root.toStyledString();
            return root.toStyledString();
        }
        if(insertUser(username,password)){
            root["registerSuccess"] = "SUCCESS";
        }

        //create CollectionRelation table
        createCollectionRelationTable();
    }else{
        auto fanBroker = FanBroker::getInstance();
        auto res =fanBroker->findUser(username);

        //用户不存在，可以注册,往数据库中添加一个用户
        if(res == NULL){
            if(insertUser(username,password)){
                root["registerSuccess"] = "SUCCESS";
            }
        }else{
            //用户存在，不可注册
            root["registerSuccess"] = "NAME_INVALID";
        }
    }

    root.toStyledString();
    return root.toStyledString();
}

//获得指定表最大id
int FanProxy::getMaxid(string tableName)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return 0;
    }

    char sql[1024];
    std::sprintf(sql,"select max(id) from %s",tableName.data());
    auto length = strlen(sql);
    mysql_real_query(&mysql,sql,length);

    int maxid;
    MYSQL_RES *result;
    MYSQL_ROW row;
    result = mysql_store_result(&mysql);
    if(result){
        if(row = mysql_fetch_row(result)){
            if(row[0] == NULL)
                maxid = 0;
            else{
            string str = row[0];
            std::stringstream in(str);
            in >> maxid;
            }
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

    char sql[1024];
    auto maxid = getMaxid("Account");
    std::sprintf(sql,"insert into Account(id,name,password) values('%d','%s','%s')",maxid,username.data(),userpassword.data());
    auto length = strlen(sql);
    if(!mysql_real_query(&mysql,sql,length)){
        cout <<"create user " << username << " success " << endl;
        return true;
    }
    return false;
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
    char sql1[1024];
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

void FanProxy::createCollectionRelationTable()
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "createCreatedSongList conect MYSQL failed!" << endl;
        return;
    }

    char sql[512];
    string str{"create table CollectionRelation(songListName char(50) not null,collecteUser char(50) not null);"};
//    std::sprintf(sql,"create table CollectionRelation(songListName char(50) not null,collecteUser char(50) not null);");
//    auto length = strlen(sql);
    if(!mysql_real_query(&mysql,"create table CollectionRelation(songListName char(50) not null,collecteUser char(50) not null);",str.size())){
        cout <<"create table CollectionRelation!" << endl;
    }
}

bool FanProxy::createAccountTable()
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "createAccountTable conect MYSQL failed!" << endl;
        return false;
    }

    //创建Account表
//    string str{"CREATE TABLE Account("
//               "id int NOT NULL AUTO_INCREMENT PRIMARY KEY,"
//               "name char(20) not null,"
//               "password char(20) not null);"};
    string str{"CREATE TABLE Account("
               "id int not null AUTO_INCREMENT PRIMARY KEY,"
               "name char(30) not null,"
               "password char(30) not null,"
               "label char(50),"
               "sex char(10),"
               "birthday date,"
               "address char(50),"
               "icon char(100),"
               "isVaild bool);"};

    auto length = str.size();
    if(!mysql_real_query(&mysql,"CREATE TABLE Account("
                         "id int not null AUTO_INCREMENT PRIMARY KEY,"
                         "name char(30) not null,"
                         "password char(30) not null,"
                         "label char(50),"
                         "sex char(10),"
                         "birthday date,"
                         "address char(50),"
                         "icon char(100),"
                         "isVaild bool);",length)){
        cout <<"create table Account!" << endl;
        return true;
    }else
        return false;
}
