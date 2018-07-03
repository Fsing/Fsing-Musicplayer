#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>
#include <string>

class DatabaseController
{
public:
    //初始化，如果没有，创建服务器在线歌曲的所有表
    DatabaseController();

    //登录用户（登录、搜索）
    std::string findUser(std::string username,std::string password);
    //登录用户
//    std::string myLogin(std::string username,std::string password);
    //注册用户
    std::string myRegister(std::string username,std::string password);
    std::string songInformation(std::string songSource);
    std::string search(std::string songKey);
    //记录创建歌单
    std::string addCreateSongList(std::string username, std::string songListName, std::string time);
    //获得最大用户表最大id
    int getMaxid();
    //创建用户表
    void createAccountTable();
    //创建用户对应的原创歌单表
     void createCreatedSongList(std::string songListName);
    //检索数据库中是否有tablename对应的表
    bool hasTable(std::string tableName);

    std::string songList(std::string songListName);

private:
//    bool m_userNameFlag;
//    bool m_userPasswordFlag;
    std::string m_userName;
    std::string m_userPassword;

};
#endif // DATABASE_H
