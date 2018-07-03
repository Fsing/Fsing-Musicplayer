#include "database.h"
#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <macro.h>
#include <sstream>
#include "macro.h"
#include "json/json.h"

using std::string;           using std::cout;
using std::endl;

//INVALID 无效
//VALID 有效，存在

DatabaseController::DatabaseController()
{
}

std::string DatabaseController::findUser(std::string username, std::string password)
{
    //姓名、密码正确返回SUCCESS
    //姓名正确、密码错误返回PW_INVALID
    //账户不存在NAME_INVALID

    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return "FAILD";
    }

    char sql[100];
    auto name = username.data();
    //    auto pw = password.data();
    std::sprintf(sql,"select * from Account WHERE name= '%s'",name);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"fondUser select * from Account failed" << endl;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        //    MYSQL_FIELD *fields;

        result = mysql_store_result(&mysql);
        if(result){
            while(row = mysql_fetch_row(result)){
                //                m_userNameFlag = true;
                if(string(row[2]) == password){
                    m_userName = row[1];
                    m_userPassword = row[2];
                    //                    m_userPassword = true;
                    return "SUCCESS";
                }else
                    return "PW_INVALID";
            }
        }
    }
    return "NAME_INVALID";
}


//std::string DatabaseController::myLogin(std::string username, std::string password)
//{
//    auto res =findUser(username,password);
//    Json::Value root;
//    Json::Value arrayObj;
//    root["type"] = "LOGIN";
//    root["userName"] = username;
//    root["userPassword"] = password;
//    root["loginSuccess"] = res;

//    MYSQL mysql;
//    mysql_init(&mysql);
//    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
//        cout << "findUser conect MYSQL failed!" << endl;
//        return "FAILD";
//    }

//    char query[255];
//    auto name = username.data();
//    sprintf(query, "select * from CreateSongList where username='%s'", name);
//    if (mysql_query(&mysql, query)) {
//        std::cout << "查询失败" << std::endl;
//    }
//    std::cout << "查询成功" << std::endl;
//    MYSQL_RES *result;
//    result = mysql_store_result(&mysql);
//    if (result) {
//        int row_num = mysql_num_rows(result);
//        std::cout << "共有" << row_num << "条数据，以下为其详细内容：" << std::endl;
//        std::cout << "row[0]" << std::endl;
//        MYSQL_ROW row;
//        while (row = mysql_fetch_row(result)){
//            std::cout << row[2] << std::endl;
//            arrayObj.append(row[2]);
//        }
//    }

//    root["array"] = arrayObj;
//    auto s = root.toStyledString();
//    return root.toStyledString();
//}
std::string DatabaseController::songInformation(std::string songSource)
{

    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return FAILD;
    }

    char sql[100];
    auto source = songSource.data();
    //    auto pw = password.data();
    std::sprintf(sql,"select * from songinfo WHERE source= '%s'",source);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"fondUser select * from Account failed" << endl;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        //    MYSQL_FIELD *fields;

        result = mysql_store_result(&mysql);
        if(result){
            while(row = mysql_fetch_row(result)){
                //                m_userNameFlag = true;
                if(string(row[1]) == source){

                    std::string songName = row[0];
                    Json::Value root;
                    root["type"] = "SONGINFO";
                    root["songName"] = songName;
                    root.toStyledString();
                    std::string out = root.toStyledString();
                    return out.data();
                }
            }
        }
    }
    return "null infomation";
}
std::string DatabaseController::search(std::string songKey)
{

    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return "FAILD";
    }

    char sql[512];
    memset(sql,0,sizeof(char)*512);
    auto key = songKey.data();
    //    auto pw = password.data();
    std::sprintf(sql,"select * from songinfo WHERE source like '%%%s%%' or songname like '%%%s%%'",key,key);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"fondUser select * from Account failed" << endl;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        //    MYSQL_FIELD *fields;

        result = mysql_store_result(&mysql);
        if(result){
            Json::Value root;
            Json::Value arrayObj;
            root["type"] = "SEARCH";
            int resultRow = 0;

            while(row = mysql_fetch_row(result)){
                //                m_userNameFlag = true;
                Json::Value item;

                item["songName"] = row[0];
                item["type"] = "SONGINFO";
                item["source"] = row[1];
                arrayObj.append(item);
                ++resultRow;
            }
            root["array"] = arrayObj;
            root["row"] = resultRow;

            root.toStyledString();
            std::string out = root.toStyledString();
            return out.data();
        }
    }
    return "null infomation";
}

std::string DatabaseController::addCreateSongList(std::string username,std::string songListName, std::string time)
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
            cout << "findUser conect MYSQL failed!" << endl;

            root["registerSuccess"] = "FAILD";
            root.toStyledString();
            return root.toStyledString();
        }

        //查询是否已经存在CreateSongList表
        auto tableName = username + "CreatedSongList";
        //
        if (!hasTable(tableName)){
            createCreatedSongList(tableName);
        }

        cout <<"exit createCreatedSongList" << endl;
        //往歌单表中插入一行歌单信息
        auto uname = username.data();
        auto lname = songListName.data();
        auto ctime = time.data();
        auto tableName1 = tableName.data();
        char sql[100];
        std::sprintf(sql,"insert into %s(username,listname,time) values('%s','%s','%s')",tableName1,uname,lname,ctime);
        auto length = strlen(sql);
        if(!mysql_real_query(&mysql,sql,length)){
            cout <<"record create song list " << lname << " success " << endl;
            root["recordSuccess"] = "SUCCESS";
        }else {
            cout <<"record create song list " << lname << " false" << endl;
            root["recordSuccess"] = "FALSE";
        }
    }else {
        cout <<"record create song list " << " false" << endl;
        root["recordSuccess"] = "FALSE";
    }
    root.toStyledString();
    return root.toStyledString();
}

std::string DatabaseController::myRegister(std::string username, std::string password)
{
    Json::Value root;
    root["type"] = "REGISTER";
    root["userName"] = username;
    root["userPassword"] = password;


    //注册成功返回SUCCESS,反之返回FAILD
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;

        root["registerSuccess"] = "FAILD";
        root.toStyledString();
        return root.toStyledString();
    }

    //创建Account表
    if(!hasTable("Account"))
        createAccountTable();
    auto ret = findUser(username,password);

    auto name = username.data();
    auto pw = password.data();
    if(ret == "NAME_INVALID"){
//        auto maxid = getMaxid();
        char sql[100];
        std::sprintf(sql,"insert into Account(name,password) values('%s','%s')",name,pw);
        auto length = strlen(sql);
        if(!mysql_real_query(&mysql,sql,length)){
            cout <<"create user " << username << " success " << endl;
            root["registerSuccess"] = "SUCCESS";
            root.toStyledString();
            return root.toStyledString();
        }
    }else {

        root["registerSuccess"] = "USER VALID";
        root.toStyledString();
        return root.toStyledString();
    }
}

int DatabaseController::getMaxid()
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return 0;
    }
    string str{"select max(id) from Account"};
    auto length = str.size();
    mysql_real_query(&mysql,"select max(id) from Account",length);

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

void DatabaseController::createAccountTable()
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return;
    }

//    //查找是否有Account表
//    MYSQL_RES *result;
//    MYSQL_ROW row;
//    char sql1[100];
//    std::sprintf(sql1,"show tables;");
//    auto length1 = std::strlen(sql1);
//    mysql_real_query(&mysql,sql1,length1);
//    result = mysql_store_result(&mysql);
//    if(result){
//        while(row = mysql_fetch_row(result)){
//            if(row[0] == "Account"){
//                return;
//            }
//        }
//    }

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
//    mysql_query(&mysql,"insert into Account(id,name,password) values(1,'jack','1234');");
}

void DatabaseController::createCreatedSongList(string songListName)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
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

bool DatabaseController::hasTable(std::string tableName)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
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

std::string DatabaseController::songList(std::string songListName)
{
    MYSQL mysql;
    mysql_init(&mysql);
    if(!mysql_real_connect(&mysql,"localhost","fsing","fsing","Fsing",3306,NULL,0)){
        cout << "findUser conect MYSQL failed!" << endl;
        return "FAILD";
    }
    char sql[512];
    memset(sql,0,sizeof(char)*512);
    auto key = songListName.data();
    //    auto pw = password.data();
    std::sprintf(sql,"select * from %s",key);
    size_t length =strlen(sql);
    int res = mysql_real_query(&mysql,sql,length);
    if(res != 0){
        cout <<"fondUser select * from Account failed" << endl;
    }else{
        MYSQL_RES *result;
        MYSQL_ROW row;
        //    MYSQL_FIELD *fields;

        result = mysql_store_result(&mysql);
        if(result){
            Json::Value root;
            Json::Value arrayObj;
            root["type"] = "SONGLIST";
            int resultRow = 0;

            while(row = mysql_fetch_row(result)){
                //                m_userNameFlag = true;
                Json::Value item;

                item["songName"] = row[1];
                item["type"] = "SONGINFO";
                item["source"] = row[2];
                item["id"] = row[0];
                arrayObj.append(item);
                ++resultRow;
            }
            root["array"] = arrayObj;
            root["row"] = resultRow;

            root.toStyledString();
            std::string out = root.toStyledString();
            return out.data();
        }
    }
    return "null infomation";
}

