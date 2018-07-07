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

    //std::thread t(run_service);
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
    //传输到服务器
    sock.write_some(buffer(s,strlen(s)),ec);
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return;
    }

    //接受服务器返回的用户信息：基本信息、用户粉丝、关注、收藏歌单、创建歌单
    char data[1024 * 5];
    memset(data,0,sizeof(char)*1024 * 5);//reset 0 to data[]
    while(strlen(data)==0){
        sock.read_some(buffer(data),ec);
    }
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return;
    }
    Json::Reader reader;
    Json::Value resultRoot;
    cout << strlen(data) << endl;
    if(!reader.parse(data, resultRoot)){
        std::cout << "json received faild" <<std::endl;
        return;
    }else {
        string ret = resultRoot["loginSuccess"].asString();
        m_result = QString::fromStdString(ret);
        cout << "login " << ret<<endl;
        if (ret == "SUCCESS"){
            m_logining = true;
            m_userName = username;
            emit resultChanged();
            _songlistNames.clear();

            //创建歌单信息
            const Json::Value arrayObj = resultRoot["array"];
            for (unsigned int i = 0; i < arrayObj.size(); i++)
            {
                Json::Value value;
                value = arrayObj[i];
                _songlistNames.append(QString::fromStdString(value["name"].asString()));

                QList<QString> ret;
                ret.append(QString::fromStdString(value["id"].asString()));
                ret.append(QString::fromStdString(value["name"].asString()));
                ret.append(QString::fromStdString(value["author"].asString()));
                ret.append(QString::fromStdString(value["createTime"].asString()));
                ret.append(QString::fromStdString(value["label"].asString()));
                ret.append(QString::fromStdString(value["info"].asString()));
                ret.append(QString::fromStdString(value["icon"].asString()));
                ret.append(QString::fromStdString(value["collectionQuantity"].asString()));
                ret.append(QString::fromStdString(value["clickQuantity"].asString()));
                ret.append(QString::fromStdString(value["shareQuantity"].asString()));

                _fan.addCreatedSongList(ret);
                for(int k = 0; k < _fan.createdSongLists()[i].size();k++)
                    cout << (_fan.createdSongLists()[i].at(k)).toStdString() << endl;
            }
            //收藏歌单信息
            const Json::Value arrayObj1 = resultRoot["collectedArray"];
            for (unsigned int i = 0; i < arrayObj1.size(); i++)
            {
                Json::Value value;
                value = arrayObj1[i];

                QList<QString> ret;
                ret.append(QString::fromStdString(value["id"].asString()));
                ret.append(QString::fromStdString(value["name"].asString()));
                ret.append(QString::fromStdString(value["author"].asString()));
                ret.append(QString::fromStdString(value["createTime"].asString()));
                ret.append(QString::fromStdString(value["label"].asString()));
                ret.append(QString::fromStdString(value["info"].asString()));
                ret.append(QString::fromStdString(value["icon"].asString()));
                ret.append(QString::fromStdString(value["collectionQuantity"].asString()));
                ret.append(QString::fromStdString(value["clickQuantity"].asString()));
                ret.append(QString::fromStdString(value["shareQuantity"].asString()));

                _fan.addCollectedSongLists(ret);
                for(int k = 0; k < _fan.collectedSongLists()[i].size();k++)
                    cout << (_fan.collectedSongLists()[i].at(k)).toStdString() << endl;
            }
            //关注用户信息
            const Json::Value arrayObj2 = resultRoot["attentedUsers"];
            for (unsigned int i = 0; i < arrayObj2.size(); i++)
            {
                Json::Value value;
                value = arrayObj2[i];

                QList<QString> ret;
                ret.append(QString::fromStdString(value["name"].asString()));
                ret.append(QString::fromStdString(value["password"].asString()));
                ret.append(QString::fromStdString(value["label"].asString()));
                ret.append(QString::fromStdString(value["sex"].asString()));
                ret.append(QString::fromStdString(value["birthday"].asString()));
                ret.append(QString::fromStdString(value["address"].asString()));
                ret.append(QString::fromStdString(value["icon"].asString()));

                _fan.addAttentedUsers(ret);
                for(int k = 0; k < _fan.attentedUsers()[i].size();k++)
                    cout << (_fan.attentedUsers()[i].at(k)).toStdString() << endl;
            }
            //粉丝信息
            const Json::Value arrayObj3 = resultRoot["fanUsers"];
            for (unsigned int i = 0; i < arrayObj3.size(); i++)
            {
                Json::Value value;
                value = arrayObj3[i];

                QList<QString> ret;
                ret.append(QString::fromStdString(value["name"].asString()));
                ret.append(QString::fromStdString(value["password"].asString()));
                ret.append(QString::fromStdString(value["label"].asString()));
                ret.append(QString::fromStdString(value["sex"].asString()));
                ret.append(QString::fromStdString(value["birthday"].asString()));
                ret.append(QString::fromStdString(value["address"].asString()));
                ret.append(QString::fromStdString(value["icon"].asString()));

                _fan.addFanUsers(ret);
                for(int k = 0; k < _fan.fanUsers()[i].size();k++)
                    cout << (_fan.fanUsers()[i].at(k)).toStdString() << endl;
            }
//            if(_songlistNames.size() != 0)
//                emit createdSongListsChanged();
            for (unsigned int i = 0; i < _songlistNames.size(); i++)
            {
                cout << _songlistNames.at(i).toStdString() << endl;
            }
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
        return;
    }
    std::cout<<"send message to server: " <<out<<endl;

    //读取服务器返回的消息：是否注册成功
    char data[512];
    memset(data,0,sizeof(char)*512);//reset 0 to data[]
    while(strlen(data)==0){
        sock.read_some(buffer(data),ec);
    }
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return;

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

QString Client::songInformation(QString songId){
    Json::Value root;
    root["type"] = "SONGINFO";
    root["songInfo"] = songId.toStdString();
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
    while(strlen(data)==0){
        sock.read_some(buffer(data),ec);
    }
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return "ERROR";

    }
    Json::Reader reader;
    Json::Value resultRoot;

    if(!reader.parse(data, resultRoot)){
        std::cout << "json received faild" <<std::endl;
        return "json received faild";
    }else {
        string ret = resultRoot["id"].asString();
        m_songName = QString::fromStdString(resultRoot["name"].asString());
        m_result = QString::fromStdString(ret);

        m_songInformation.append(QString::fromStdString(resultRoot["id"].asString()));
        m_songInformation.append(QString::fromStdString(resultRoot["name"].asString()));
        m_songInformation.append(QString::fromStdString(resultRoot["singer"].asString()));
        m_songInformation.append(QString::fromStdString(resultRoot["album"].asString()));
        m_songInformation.append(QString::fromStdString(resultRoot["source"].asString()));
        m_songInformation.append(QString::fromStdString(resultRoot["playQuantity"].asString()));
        m_songInformation.append(QString::fromStdString(resultRoot["downloadQuantity"].asString()));
        m_songInformation.append(QString::fromStdString(resultRoot["shareQuantity"].asString()));

        std::cout <<"receive frome server : "<< data <<std::endl;
        return m_songName;
    }
}

void Client::fileTransfer(QString fileName){
    auto filename = fileName.toStdString().data();
    FILE *fp = fopen(filename, "rb");
    if (fp != NULL) {
        cout << "find previous file" <<fileName.toStdString()<<endl;
        return;
    }

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


    char data[1024*5];
    memset(data,0,sizeof(char)*1024*5);//reset 0 to data[]
    while(strlen(data)==0){
        sock.read_some(buffer(data),ec);
    }
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


void Client::songList(QString songListId){
    Json::Value root;
    root["type"] = "SONGLIST";
    root["songListId"] = songListId.toStdString();
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


    char data[1024*5];
    memset(data,0,sizeof(char)*1024*5);//reset 0 to data[]
    while(strlen(data)==0){
        sock.read_some(buffer(data),ec);
    }
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return;

    }
    Json::Reader reader;
    Json::Value resultRoot;

    if (reader.parse(data, resultRoot))
    {
        const Json::Value arrayObj = resultRoot["array"];
        m_songListInformation.clear();
        m_songList.clear();

        m_songListInformation.append( QString::fromStdString( resultRoot["id"].asString()));
        m_songListInformation.append( QString::fromStdString( resultRoot["name"].asString()));
        m_songListInformation.append( QString::fromStdString( resultRoot["author"].asString()));
        m_songListInformation.append( QString::fromStdString( resultRoot["createTime"].asString()));
        m_songListInformation.append( QString::fromStdString( resultRoot["label"].asString()));
        m_songListInformation.append( QString::fromStdString( resultRoot["info"].asString()));
        m_songListInformation.append( QString::fromStdString( resultRoot["icon"].asString()));
        m_songListInformation.append( QString::fromStdString( resultRoot["collectionQuantity"].asString()));
        m_songListInformation.append( QString::fromStdString( resultRoot["clickQuantity"].asString()));
        m_songListInformation.append( QString::fromStdString( resultRoot["shareQuantity"].asString()));

        for (unsigned int i = 0; i < arrayObj.size(); i++)
        {
            m_songList.append( QString::fromStdString( arrayObj[i]["id"].asString()));
            m_songList.append( QString::fromStdString( arrayObj[i]["name"].asString()));
            m_songList.append( QString::fromStdString( arrayObj[i]["singer"].asString()));
            m_songList.append( QString::fromStdString( arrayObj[i]["album"].asString()));
            m_songList.append( QString::fromStdString( arrayObj[i]["source"].asString()));
            m_songList.append( QString::fromStdString( arrayObj[i]["playQuantity"].asString()));
            m_songList.append( QString::fromStdString( arrayObj[i]["shareQuantity"].asString()));
            m_songList.append( QString::fromStdString( arrayObj[i]["downloadQuantity"].asString()));
        }
        std::cout <<"receive frome server : "<< data <<std::endl;
        return;
    }
    cout<<"json receive failed"<<endl;
}
void Client::interface(QString interfaceName){
    Json::Value root;
    root["type"] = "INTERFACE";
    root["interfaceName"] = interfaceName.toStdString();
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


    char data[1024*5];
    memset(data,0,sizeof(char)*1024*5);//reset 0 to data[]
    while(strlen(data)==0){
        sock.read_some(buffer(data),ec);
    }
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return;
    }
    Json::Reader reader;
    Json::Value resultRoot;
    if (reader.parse(data, resultRoot))
    {
        const Json::Value arrayObj = resultRoot["array"];
        for (unsigned int i = 0; i < arrayObj.size(); i++)
        {
            m_interface.append( QString::fromStdString( arrayObj[i]["id"].asString()));
            m_interface.append( QString::fromStdString( arrayObj[i]["name"].asString()));
            m_interface.append( QString::fromStdString( arrayObj[i]["author"].asString()));
            m_interface.append( QString::fromStdString( arrayObj[i]["createTime"].asString()));
            m_interface.append( QString::fromStdString( arrayObj[i]["label"].asString()));
            m_interface.append( QString::fromStdString( arrayObj[i]["info"].asString()));
            m_interface.append( QString::fromStdString( arrayObj[i]["icon"].asString()));
            m_interface.append( QString::fromStdString( arrayObj[i]["collectionQuantity"].asString()));
            m_interface.append( QString::fromStdString( arrayObj[i]["clickQuantity"].asString()));
            m_interface.append( QString::fromStdString( arrayObj[i]["shareQuantity"].asString()));

        }
        std::cout <<"receive frome server : "<< data <<std::endl;
        return;
    }
}



//**************************

void Client::fileReceiver(){
    clock_ = clock();
    sock.receive(buffer(reinterpret_cast<char*>(&file_info_), sizeof(file_info_)));
    if(file_info_.filename_size == 0){
        std::cout<<"file is not exist"<<std::endl;
        return;
    }
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

    fp_ = fopen(basename, "wb");
    if (fp_ == NULL) {
        std::cerr << "Failed to open file to write\n";
        return;
    }
    string fileName = basename;
    receive_file_content(fileName);
}

void Client::receive_file_content(string fileName)
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
    cout << "transfer successful " << fileName<<endl;
}

void Client::addCreateSongList(QString username,QString songlistName, QString time)
{
    _songlistNames.append(songlistName);
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
        return;
    }
    std::cout<<"send message to server: " <<out<<endl;

    //读取服务器返回的消息：是否成功记录
    char data[512];
    memset(data,0,sizeof(char)*512);//reset 0 to data[]
    while(strlen(data)==0){
        sock.read_some(buffer(data),ec);
    }
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return;

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

