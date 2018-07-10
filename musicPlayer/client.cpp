#include <client.h>
#include <boost/asio.hpp>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <boost/thread.hpp>
#include "client.h"
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
ip::tcp::socket sock_fileTransfer(service);

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
    sock_fileTransfer.async_connect(ep,[](const error_code &e){
        if(e){
            cout << e.message() << endl;
            return;
        }
    });
    service.run();
}

void Client::writeUserConfig()
{
    //    ofstream
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
    char data[1024 * 10];
    memset(data,0,sizeof(char)*1024 * 10);//reset 0 to data[]
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
        m_result =  QString::fromStdString(ret);
        cout << "login " << ret<<endl;
        if (ret == "SUCCESS"){
            _songlistNames.clear();
            _collectedSongListNames.clear();
            _songlistIDs.clear();
            _fan.clear();

            _fan.setUsername(QString::fromStdString(resultRoot["userName"].asString()));
            _fan.setPassword(QString::fromStdString(resultRoot["userPassword"].asString()));
            _fan.setLabel(QString::fromStdString(resultRoot["userLabel"].asString()));
            _fan.setSex(QString::fromStdString(resultRoot["userSex"].asString()));
            _fan.setBirthday(QString::fromStdString(resultRoot["userBirthday"].asString()));
            _fan.setAddress(QString::fromStdString(resultRoot["userAddress"].asString()));
            _fan.setIcon(QString::fromStdString(resultRoot["userIcon"].asString()));

            //设置用户信息
            m_logining = true;
            m_userName = username;
            m_icon = _fan.icon();
            emit userIconChanged();
            emit userNameChanged();
            emit resultChanged();


            //创建歌单信息
            const Json::Value arrayObj = resultRoot["array"];
            for (unsigned int i = 0; i < arrayObj.size(); i++)
            {
                Json::Value value;
                value = arrayObj[i];
                //存储原创歌单名字
                _songlistNames.append(QString::fromStdString(value["name"].asString()));
                _songlistIDs.append(QString::fromStdString(value["id"].asString()));

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

                _fan.addCreatedSongList(QString::fromStdString(value["name"].asString()),ret);
                //                for(int k = 0; k < _fan.createdSongLists()[i].size();k++)
                //                    cout << (_fan.createdSongLists()[i].at(k)).toStdString() << endl;
            }
            m_CreatedSongListCount = _fan.createdSongListCount();
            emit createdSongListCountChanged();
            //收藏歌单信息
            const Json::Value arrayObj1 = resultRoot["collectedArray"];
            for (unsigned int i = 0; i < arrayObj1.size(); i++)
            {
                Json::Value value;
                value = arrayObj1[i];
                //存储收藏歌单名字
                _collectedSongListNames.append(QString::fromStdString(value["name"].asString()));
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

                _fan.addCollectedSongLists(QString::fromStdString(value["name"].asString()),ret);
                //                for(int k = 0; k < _fan.collectedSongLists()[i].size();k++)
                //                    cout << (_fan.collectedSongLists()[i].at(k)).toStdString() << endl;
            }
            m_collectedSongListCount = _fan.collectedSongListCount();
            emit collecedSongListCountChanged();
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

                _fan.addAttentedUsers(QString::fromStdString(value["name"].asString()),ret);
                //                for(int k = 0; k < _fan.attentedUsers()[i].size();k++)
                //                    cout << (_fan.attentedUsers()[i].at(k)).toStdString() << endl;
            }
            m_attentedUserCount = _fan.attentionUserCount();
            emit attentionUserCountChanged();
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

                _fan.addFanUsers(QString::fromStdString(value["name"].asString()),ret);
                //                for(int k = 0; k < _fan.fanUsers()[i].size();k++)
                //                    cout << (_fan.fanUsers()[i].at(k)).toStdString() << endl;
            }
            m_fanUserCount = _fan.fanUserCount();
            emit fanUserCountChanged();
            //            if(_songlistNames.size() != 0)
            //                emit createdSongListsChanged();
            for (unsigned int i = 0; i < _songlistNames.size(); i++)
            {
                cout << _songlistNames.at(i).toStdString() << endl;
            }
        }
        //socket_fileTransfer请求传送用户头像
        cout << "请求头像： " << _fan.icon().toStdString() << endl;
        fileTransfer(_fan.icon());
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
QString Client::songInformationBySource(QString source){
    for(auto &l:m_songsMap){
        auto song = l.second;
        if(song->getSource() == source.toStdString()){
            return QString::fromStdString( song->getName());
        }
    }
}
QString Client::songInformation(QString songId){
    m_songInformation.clear();
    auto iter = m_songsMap.find(songId.toInt());
    if(iter != m_songsMap.end()){
        std::cout << "find previous song in song cache pool " << std::endl;
        auto song = iter->second;
        m_songInformation.append(QString::number(song->getId()));
        m_songInformation.append(QString::fromStdString(song->getName()));
        m_songInformation.append(QString::fromStdString(song->getSinger()));
        m_songInformation.append(QString::fromStdString(song->getAlbum()));
        m_songInformation.append(QString::fromStdString(song->getSource()));
        m_songInformation.append(QString::number(song->getPlayQuantity()));
        m_songInformation.append(QString::number(song->getDownloadQuantity()));
        m_songInformation.append(QString::number(song->getShareQuantity()));
        return QString::fromStdString(song->getName());
    }else{

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

            m_songInformation.append(QString::number(resultRoot["id"].asInt()));
            m_songInformation.append(QString::fromStdString(resultRoot["name"].asString()));
            m_songInformation.append(QString::fromStdString(resultRoot["singer"].asString()));
            m_songInformation.append(QString::fromStdString(resultRoot["album"].asString()));
            m_songInformation.append(QString::fromStdString(resultRoot["source"].asString()));
            m_songInformation.append(QString::number(resultRoot["playQuantity"].asInt()));
            m_songInformation.append(QString::number(resultRoot["downloadQuantity"].asInt()));
            m_songInformation.append(QString::number(resultRoot["shareQuantity"].asInt()));

            //add to song cache pool
            std::shared_ptr<Song> retSong = std::make_shared<Song>(
                        Song(resultRoot["id"].asInt(),
                        resultRoot["name"].asString(),
                    resultRoot["singer"].asString(),
                    resultRoot["album"].asString(),
                    resultRoot["source"].asString(),
                    resultRoot["playQuantity"].asInt(),
                    resultRoot["shareQuantity"].asInt(),
                    resultRoot["downloadQuantity"].asInt()));
            m_songsMap.insert(std::make_pair(resultRoot["id"].asInt(),retSong));



            std::cout <<"receive frome server : "<< data <<std::endl;
            return m_songName;
        }
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
    sock_fileTransfer.write_some(buffer(s,strlen(s)),ec);
    std::cout<<"send message to server: " <<out<<endl;
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return;
    }

    fileReceiver();
}

QList<QString> Client::search(QString key){
    Json::Value root;
    root["type"] = "SEARCH";
    root["songKey"] = key.toStdString();
    root.toStyledString();
    std::string out = root.toStyledString();
    auto s = out.data();
    boost::system::error_code ec;
    sock.write_some(buffer(s,strlen(s)),ec);
    std::cout<<"send message to server: " <<out<<endl;
    QList<QString> ret;
    if(ec)
    {

        std::cout << boost::system::system_error(ec).what() << std::endl;
        return ret;
    }


    char data[1024*5];
    memset(data,0,sizeof(char)*1024*5);//reset 0 to data[]
    //-----------------------
    boost::posix_time::ptime time_now,time_now1;
    boost::posix_time::millisec_posix_time_system_config::time_duration_type time_elapse;
    time_now = boost::posix_time::second_clock::universal_time();

    // 得到两个时间间隔的秒数;
    int sec = 0;
    while(strlen(data)==0 && sec <= 2){
        sock.read_some(buffer(data),ec);
        time_now1 = boost::posix_time::second_clock::universal_time();
        time_elapse = time_now1 - time_now;
        sec = time_elapse.total_seconds();
        cout <<sec<<endl;
    }
    if(strlen(data) == 0){
        return ret;
    }

    //---------------------------
    if(ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
        return ret;
    }


    Json::Reader reader;
    Json::Value resultRoot;


    if (reader.parse(data, resultRoot))
    {
        const Json::Value arrayObj = resultRoot["array"];
        for (unsigned int i = 0; i < arrayObj.size(); i++)
        {
            //add to song cache pool
            if(arrayObj[i]["type"] == "SONGINFO"){
                std::shared_ptr<Song> retSong = std::make_shared<Song>(
                            Song(std::stoi(arrayObj[i]["id"].asString()),
                            arrayObj[i]["name"].asString(),
                        arrayObj[i]["singer"].asString(),
                        arrayObj[i]["album"].asString(),
                        arrayObj[i]["source"].asString(),
                        std::stoi(arrayObj[i]["playQuantity"].asString()),
                        std::stoi(arrayObj[i]["shareQuantity"].asString()),
                        std::stoi(arrayObj[i]["downloadQuantity"].asString())));
                m_songsMap.insert(std::make_pair(std::stoi(arrayObj[i]["id"].asString()),retSong));
                //add to Qlist
                ret.append(QString::fromStdString(arrayObj[i]["id"].asString()));
                ret.append(QString::fromStdString(arrayObj[i]["name"].asString()));
                ret.append(QString::fromStdString(arrayObj[i]["singer"].asString()));
                ret.append(QString::fromStdString(arrayObj[i]["album"].asString()));
                ret.append(QString::fromStdString(arrayObj[i]["source"].asString()));
                ret.append(QString::fromStdString(arrayObj[i]["playQuantity"].asString()));
                ret.append(QString::fromStdString(arrayObj[i]["shareQuantity"].asString()));
                ret.append(QString::fromStdString(arrayObj[i]["downloadQuantity"].asString()));
            }
            //------------------------------
        }
        std::cout <<"receive frome server : "<< data <<std::endl;
        m_searchCount = arrayObj.size();
        return ret;
    }
    return ret;
}


void Client::songList(QString songListId){
    if(m_songlistsMap.find(songListId.toInt()) != m_songlistsMap.end()){
        std::cout << "find previous songlist "<< songListId.toStdString() << std::endl;
    }else{
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
        if (reader.parse(data, resultRoot)){
            const Json::Value arrayObj = resultRoot["array"];

            std::shared_ptr<SongList> ret = std::make_shared<SongList>(SongList(resultRoot["id"].asInt(),
                                                                       resultRoot["name"].asString(),
                    resultRoot["author"].asString(),
                    resultRoot["createTime"].asString(),
                    resultRoot["label"].asString(),
                    resultRoot["info"].asString(),
                    resultRoot["icon"].asString(),
                    resultRoot["collectionQuantity"].asInt(),
                    resultRoot["clickQuantity"].asInt(),
                    resultRoot["shareQuantity"].asInt()));
            std::map<int,std::shared_ptr<Song>> songs;
            for (unsigned int i = 0; i < arrayObj.size(); i++)
            {
                std::shared_ptr<Song> retSong = std::make_shared<Song>(
                            Song(arrayObj[i]["id"].asInt(),
                            arrayObj[i]["name"].asString(),
                        arrayObj[i]["singer"].asString(),
                        arrayObj[i]["album"].asString(),
                        arrayObj[i]["source"].asString(),
                        arrayObj[i]["playQuantity"].asInt(),
                        arrayObj[i]["shareQuantity"].asInt(),
                        arrayObj[i]["downloadQuantity"].asInt()));
                songs.insert(std::make_pair(arrayObj[i]["id"].asInt(),retSong));

                //add to song cache pool
                m_songsMap.insert(std::make_pair(arrayObj[i]["id"].asInt(),retSong));
            }
            ret->setSongs(songs);
            m_songlistsMap.insert(std::make_pair(resultRoot["id"].asInt(),ret)) ;
            std::cout <<"receive frome server : "<< data <<std::endl;
            return;
        }
    }
    cout<<"json receive failed"<<endl;
    return;
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


    char data[1024*10];
    memset(data,0,sizeof(char)*1024*10);//reset 0 to data[]
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
        const Json::Value advertArrayObj = resultRoot["advertArray"];
        for (unsigned int i = 0; i < advertArrayObj.size(); i++)
        {
            m_interface.append(QString::fromStdString( advertArrayObj[i]["source"].asString()));
        }
        std::cout <<"receive frome server : "<< data <<std::endl;
        return;
    }
}

QList<QString> Client::attentedUsers(){
    QList<QString> ret;
    auto it = _fan.attentedUsers().begin();
    //    cout << attentionUserCount() << endl;
    for(auto it = _fan.attentedUsers().constBegin();it!= _fan.attentedUsers().constEnd();it++)
    {
        ret.append(it.value().at(0));
        ret.append(it.value().at(6));
    }

    return ret;
}
QList<QString> Client::fanUsers(){
    QList<QString> ret;
    for(auto it = _fan.fanUsers().constBegin();it!= _fan.fanUsers().constEnd();it++)
    {
        ret.append(it.value().at(0));
        ret.append(it.value().at(6));
    }

    return ret;
}


//**************************

void Client::fileReceiver(){

    clock_ = clock();
    sock_fileTransfer.receive(buffer(reinterpret_cast<char*>(&file_info_), sizeof(file_info_)));
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
    read(sock_fileTransfer, buffer(buffer_, file_info_.filename_size));
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
        bytes_transferred = sock_fileTransfer.receive(buffer(buffer_, k_buffer_size));
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
        string ret = resultRoot["recordSuccess"].asString();
        cout << "record create song list " << ret<<endl;
        if(ret == "SUCCESS"){
            QList<QString> list;
            list.append("");
            list.append(songlistName);
            list.append(username);
            list.append(time);
            list.append("");
            list.append("");
            list.append("");
            list.append("");
            list.append("");
            list.append("");
            _fan.addCreatedSongList(songlistName,list);
            m_CreatedSongListCount++;
            _songlistNames.append(songlistName);

            emit createdSongListCountChanged();
        }
        return;
    }
}

void Client::addSongToSongList(QString songListID, QString songID)
{
    Json::Value root;
    root["type"] = "ADDSONGTOSONGLIST";
    root["songListID"] = songListID.toStdString();
    root["songID"] = songID.toStdString();
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
        string ret = resultRoot["recordSuccess"].asString();
        cout << "record create song list " << ret<<endl;
        if(ret == "SUCCESS"){
           cout << "Add Song To SongList Success!" << endl;
        }
        return;
    }
}

//void Client::run_service()
//{
//    service.run();
//}
//--------------get--------------
QList<QString> Client::getSongListInformation(QString songListId){
    if(songListId != ""){
        int tmp = songListId.toInt();
        auto songList = m_songlistsMap[tmp];
        QList<QString> ret;
        ret.clear();

        ret.append(QString::number(songList->getId()));
        ret.append(QString::fromStdString(songList->getName()));
        ret.append(QString::fromStdString(songList->getAuthor()));
        ret.append(QString::fromStdString(songList->getCreateTime()));
        ret.append(QString::fromStdString(songList->getLabel()));
        ret.append(QString::fromStdString(songList->getInfo()));
        ret.append(QString::fromStdString(songList->getIcon()));
        ret.append(QString::number(songList->getCollectionQuantity()));
        ret.append(QString::number(songList->getClickQuantity()));
        ret.append(QString::number(songList->getShareQuantity()));
        return ret;
    }
}
QList<QString> Client::getSongListSongs(QString songListId){
    std::cout << "exec Client::getSongListSongs" << std::endl;
    if(songListId != ""){
        std::cout << "songListId: " << songListId.toInt() << std::endl;
        std::shared_ptr<SongList> songlist = m_songlistsMap[songListId.toInt()];
        QList<QString> ret;
        ret.clear();

        auto songs = songlist->getSongs();
        for(auto &l : songs){
            auto song = l.second;
            ret.append(QString::number(song->getId()));
            ret.append(QString::fromStdString(song->getName()));
            ret.append(QString::fromStdString(song->getSinger()));
            ret.append(QString::fromStdString(song->getAlbum()));
            ret.append(QString::fromStdString(song->getSource()));
            ret.append(QString::number(song->getPlayQuantity()));
            ret.append(QString::number(song->getDownloadQuantity()));
            ret.append(QString::number(song->getShareQuantity()));
        }
        m_songListCount = ret.size()/8;
        return ret;
    }
}
