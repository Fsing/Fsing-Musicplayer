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
    memset(buffer_,0,sizeof(char)*k_buffer_size);
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
    if (ret == "SUCCESS")
        m_logining = true;

    m_userName = username;
    emit resultChanged();

    _songlistNames.clear();
    const Json::Value arrayObj = resultRoot["array"];
    for (unsigned int i = 0; i < arrayObj.size(); i++)
    {
        _songlistNames.append(QString::fromStdString(arrayObj[i].asString()));

    }
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

void Client::fileTransfer(QString fileName){
    Json::Value root;
    root["type"] = "FILETRANSFER";
    root["fileName"] = fileName.toStdString();
    root.toStyledString();
    std::string out = root.toStyledString();
    auto s = out.data();

    boost::system::error_code ec;
    sock.write_some(buffer(s,strlen(s)),ec);
            std::cout<<"send message to server: " <<out<<endl;
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return;
    }

    fileReceiver();
    cout << "transfer successful " << fileName.toStdString()<<endl;
}

QString Client::search(QString key){
    Json::Value root;
    root["type"] = "SEARCH";
    root["songKey"] = key.toStdString();
    root.toStyledString();
    std::string out = root.toStyledString();
    auto s = out.data();
    boost::system::error_code ec;
    sock.write_some(buffer(s,strlen(s)),ec);
            std::cout<<"send message to server: " <<out<<endl;
    if(ec)
    {

        std::cout << boost::system::system_error(ec).what() << std::endl;
        return "ERROR";
    }


    char data[512];
    memset(data,0,sizeof(char)*512);//reset 0 to data[]
    sock.read_some(buffer(data),ec);
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
                return "ERROR";
    }


    Json::Reader reader;
    Json::Value resultRoot;

    if (reader.parse(data, resultRoot))
    {
        const Json::Value arrayObj = resultRoot["array"];
        for (unsigned int i = 0; i < arrayObj.size(); i++)
        {
            //------------------------------
        }
        std::cout <<"receive frome server : "<< data <<std::endl;
        return QString::number(arrayObj.size());
    }

    return "ERROR";
}


void Client::songList(QString songListName){
    Json::Value root;
    root["type"] = "SONGLIST";
    root["songListName"] = songListName.toStdString();
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

        if (reader.parse(data, resultRoot))
        {
            const Json::Value arrayObj = resultRoot["array"];
            for (unsigned int i = 0; i < arrayObj.size(); i++)
            {

                m_songList.append( QString::fromStdString( arrayObj[i]["id"].asString()));
                m_songList.append( QString::fromStdString( arrayObj[i]["songName"].asString()));
                m_songList.append( QString::fromStdString( arrayObj[i]["source"].asString()));

            }
            std::cout <<"receive frome server : "<< data <<std::endl;
            return;
        }
}




//**************************

void Client::fileReceiver(){
    clock_ = clock();
    sock.receive(buffer(reinterpret_cast<char*>(&file_info_), sizeof(file_info_)));
    boost::system::error_code error;
    handle_header(error);
}
void Client::handle_header(const boost::system::error_code& error)
{
    if (error) {
      std::cout << boost::system::system_error(error).what() << std::endl;
    };
  size_t filename_size = file_info_.filename_size;
  if (filename_size > k_buffer_size) {
    std::cerr << "Path name is too long!\n";
    return;
  }
  //得用async_read, 不能用async_read_some，防止路径名超长时，一次接收不完
    read(sock, buffer(buffer_, file_info_.filename_size));
    handle_file(error);
}

void Client::handle_file(const boost::system::error_code& error)
{
    if (error) {
      std::cout << boost::system::system_error(error).what() << std::endl;
    };
  const char *basename = buffer_ + file_info_.filename_size - 1;
  while (basename >= buffer_ && (*basename != '\\' && *basename != '/')) --basename;
  ++basename;

  std::cout << "Open file: " << basename << " (" << buffer_ << ")\n";

  fp_ = fopen(basename, "wb");
  if (fp_ == NULL) {
    std::cerr << "Failed to open file to write\n";
    return;
  }
  receive_file_content();
}

void Client::receive_file_content()
{

  boost::system::error_code error;
  size_t bytes_transferred = 0;
  total_bytes_writen_ = 0;

  while(total_bytes_writen_ != file_info_.filesize){
      bytes_transferred = sock.receive(buffer(buffer_, k_buffer_size));
      //bytes_transferred = strlen(buffer_);
  if (error) {
    if (error != error::eof)
        return;
    File_info::Size_type filesize = file_info_.filesize;
    if (total_bytes_writen_ != filesize)
        std::cerr <<  "Filesize not matched! " << total_bytes_writen_
          << "/" << filesize << "\n";
    return;
  }
  total_bytes_writen_ += fwrite(buffer_, 1, bytes_transferred, fp_);
  }
  fclose(fp_);
}

void Client::addCreateSongList(QString username,QString songlistName, QString time)
{
    Json::Value root;
    root["type"] = "CREATESONGLIST";
    root["username"] = username.toStdString();
    root["songListName"] = songlistName.toStdString();
    root["createTime"] = time.toStdString();
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

    //读取服务器返回的消息：是否成功记录
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
    string ret = resultRoot["record"].asString();
    cout << "record create song list " << ret<<endl;
    return;
    }
}

//void Client::run_service()
//{
//    service.run();
//}

