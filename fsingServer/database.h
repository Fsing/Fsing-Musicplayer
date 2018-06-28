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
    std::string myLogin(std::string username,std::string password);
    //注册用户
    std::string myRegister(std::string username,std::string password);
    std::string songInformation(std::string songSource);
    std::string search(std::string songKey);
    //获得最大用户表最大id
    int getMaxid();
    //查看是否有Account表,没有则创建
    void hasAccountTable();

private:
//    bool m_userNameFlag;
//    bool m_userPasswordFlag;
    std::string m_userName;
    std::string m_userPassword;

};
#endif // DATABASE_H
