#include <client.h>
#include <boost/asio.hpp>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <boost/thread.hpp>
#include "macro.h"
#include "json/json.h"

using boost::asio::io_service;
using namespace boost::asio;
using boost::asio::ip::address;
using boost::system::error_code;
using std::ifstream;                using std::endl;
using std::ofstream;                using std::cout;
using std::string;
using std::stringstream;

//typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
io_service service;
ip::tcp::endpoint ep(address::from_string("127.0.0.1"),2001);
//客户端异步连接，有多个套接字，每次发送信息、接受信息都重新分配一个套接字，并且分配一个线程独立进行
ip::tcp::socket sock(service);

Client::Client()
{
    myConnect();
}
void Client::myConnect()
{
    //    ip::tcp::socket sock(service);
    boost::system::error_code e;
    sock.async_connect(ep,[](const error_code &e){
        if(e){
            cout << e.message() << endl;
            return;
        }
    });

    //    std::thread t(run_service);
    //    t.detach();
    //    boost::thread(run_service);
    //    return sock;
    service.run();
}

void Client::readUserConfig()
{
    ifstream in("User_Config");

    string str;
    if(std::getline(in,str) && str !=""){
        string name;
        stringstream ss(str);
        ss >> name;
        m_userName = QString::fromStdString(name);
        //        }
        //        if(std::getline(in,str)){
        //            string password;
        //            stringstream sss(str);
        //            sss >> password;
        //            m_userPassWord = QString::fromStdString(password);
        //        }
        in.close();
    }else{
        ofstream out("Frozen_Config");
        m_userName ="";
        //        m_userPassWord = "";
        out << m_userName.toStdString() << endl;
        //        out << m_userPassWord.toStdString() << endl;
        out.close();
    }
}

void Client::myLogin(QString username, QString userpw)
{
    Json::Value root;
    root["type"] = "LOGIN";
    root["userName"] = username.toStdString();
    root["userPassword"] = userpw.toStdString();
    root.toStyledString();
    std::string out = root.toStyledString();

    auto s = out.data();
    boost::system::error_code ec;
    sock.write_some(buffer(s,strlen(s)),ec);
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
    }

    //接受服务器返回的用户信息：基本信息、用户粉丝、关注、收藏歌单、创建歌单
    char data[512];
    memset(data,0,sizeof(char)*512);//reset 0 to data[]
    sock.read_some(buffer(data),ec);
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
    }
    Json::Reader reader;
    Json::Value resultRoot;
    if(!reader.parse(data, resultRoot)){
      std::cout << "json received faild" <<std::endl;
      return;
    }else {
    string ret = resultRoot["loginSuccess"].asString();
    m_result = QString::fromStdString(ret);
    cout << "login " << ret<<endl;

    emit resultChanged();
    }
}

void Client::myRegister(QString username, QString userpw)
{
    Json::Value root;
    root["type"] = "REGISTER";
    root["userName"] = username.toStdString();
    root["userPassword"] = userpw.toStdString();
    root.toStyledString();
    std::string out = root.toStyledString();

    auto s = out.data();
    boost::system::error_code ec;
    sock.write_some(buffer(s,strlen(s)),ec);
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
    }
    std::cout<<"send message to server: " <<out<<endl;

    //读取服务器返回的消息：是否注册成功
    char data[512];
    memset(data,0,sizeof(char)*512);//reset 0 to data[]
    sock.read_some(buffer(data),ec);
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;

    }
    cout << "receive from server : " << data<<endl;
    Json::Reader reader;
    Json::Value resultRoot;
    if(!reader.parse(data, resultRoot)){
      std::cout << "json received faild" <<std::endl;
      return;
    }else {
    string ret = resultRoot["registerSuccess"].asString();
    m_result = QString::fromStdString(ret);
    cout << "register " << ret<<endl;
    emit resultChanged();
    return;
    }
}

QString Client::songInformation(QString songSource){
    Json::Value root;
    root["type"] = "SONGINFO";
    root["songInfo"] = songSource.toStdString();
    root.toStyledString();
    std::string out = root.toStyledString();

    auto s = out.data();
    boost::system::error_code ec;
    sock.write_some(buffer(s,strlen(s)),ec);
            std::cout<<"send message to server: " <<out<<endl;
    if(ec)
    {

        std::cout << boost::system::system_error(ec).what() << std::endl;
    }


    char data[512];
    memset(data,0,sizeof(char)*512);//reset 0 to data[]
    sock.read_some(buffer(data),ec);
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;

    }
    Json::Reader reader;
    Json::Value resultRoot;
    if(!reader.parse(data, resultRoot)){
      std::cout << "json received faild" <<std::endl;
      return "json received faild";
    }else {
    string ret = resultRoot["songName"].asString();;
    m_result = QString::fromStdString(ret);
    std::cout <<"receive frome server : "<< m_result.toStdString() <<std::endl;
    return m_result;
    }
}

void Client::addCreateSongList(QString songlistName)
{

}
//void Client::run_service()
//{
//    service.run();
//}

