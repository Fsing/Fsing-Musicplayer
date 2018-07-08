//#include "fanproxy.h"
//#include <client.h>
//#include <thread>
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <iostream>
//#include <algorithm>
//#include <boost/thread.hpp>
//#include "macro.h"
//#include "json/json.h"

//using boost::asio::io_service;
//using namespace boost::asio;
//using boost::asio::ip::address;
//using boost::system::error_code;
//using std::ifstream;                using std::endl;
//using std::ofstream;                using std::cout;
//using std::string;
//using std::stringstream;

//void FanProxy::myLogin(QString username, QString userpw, ip::tcp::socket &sock)
//{
//    Json::Value root;
//    root["type"] = "LOGIN";
//    root["userName"] = username.toStdString();
//    root["userPassword"] = userpw.toStdString();
//    root.toStyledString();
//    std::string out = root.toStyledString();

//    auto s = out.data();
//    boost::system::error_code ec;
//    //传输到服务器
//    sock.write_some(buffer(s,strlen(s)),ec);
//    if(ec)
//    {
//        std::cout << boost::system::system_error(ec).what() << std::endl;
//        return;
//    }

//    //接受服务器返回的用户信息：基本信息、用户粉丝、关注、收藏歌单、创建歌单
//    char data[1024 * 5];
//    memset(data,0,sizeof(char)*1024 * 5);//reset 0 to data[]
//    while(strlen(data)==0){
//        sock.read_some(buffer(data),ec);
//    }
//    if(ec)
//    {
//        std::cout << boost::system::system_error(ec).what() << std::endl;
//        return;
//    }
//    Json::Reader reader;
//    Json::Value resultRoot;
//    cout << strlen(data) << endl;
//    if(!reader.parse(data, resultRoot)){
//        std::cout << "json received faild" <<std::endl;
//        return;
//    }else {
//        string ret = resultRoot["loginSuccess"].asString();
//        _client.setResult(QString::fromStdString(ret));
//        cout << "login " << ret<<endl;
//        if (_client.result() == "SUCCESS"){
//            _client.setLogining(true);
////            m_userName = username;
//            emit resultChanged();
//            _client.createdSongLists().clear();

//            //创建歌单信息
//            const Json::Value arrayObj = resultRoot["array"];
//            for (unsigned int i = 0; i < arrayObj.size(); i++)
//            {
//                Json::Value value;
//                value = arrayObj[i];
//                _songlistNames.append(QString::fromStdString(value["name"].asString()));

//                QList<QString> ret;
//                ret.append(QString::fromStdString(value["id"].asString()));
//                ret.append(QString::fromStdString(value["name"].asString()));
//                ret.append(QString::fromStdString(value["author"].asString()));
//                ret.append(QString::fromStdString(value["createTime"].asString()));
//                ret.append(QString::fromStdString(value["label"].asString()));
//                ret.append(QString::fromStdString(value["info"].asString()));
//                ret.append(QString::fromStdString(value["icon"].asString()));
//                ret.append(QString::fromStdString(value["collectionQuantity"].asString()));
//                ret.append(QString::fromStdString(value["clickQuantity"].asString()));
//                ret.append(QString::fromStdString(value["shareQuantity"].asString()));

//                _fan.addCreatedSongList(QString::fromStdString(value["name"].asString()),ret);
////                for(int k = 0; k < _fan.createdSongLists()[i].size();k++)
////                    cout << (_fan.createdSongLists()[i].at(k)).toStdString() << endl;
//            }
//            //收藏歌单信息
//            const Json::Value arrayObj1 = resultRoot["collectedArray"];
//            for (unsigned int i = 0; i < arrayObj1.size(); i++)
//            {
//                Json::Value value;
//                value = arrayObj1[i];

//                QList<QString> ret;
//                ret.append(QString::fromStdString(value["id"].asString()));
//                ret.append(QString::fromStdString(value["name"].asString()));
//                ret.append(QString::fromStdString(value["author"].asString()));
//                ret.append(QString::fromStdString(value["createTime"].asString()));
//                ret.append(QString::fromStdString(value["label"].asString()));
//                ret.append(QString::fromStdString(value["info"].asString()));
//                ret.append(QString::fromStdString(value["icon"].asString()));
//                ret.append(QString::fromStdString(value["collectionQuantity"].asString()));
//                ret.append(QString::fromStdString(value["clickQuantity"].asString()));
//                ret.append(QString::fromStdString(value["shareQuantity"].asString()));

//                _fan.addCollectedSongLists(QString::fromStdString(value["name"].asString()),ret);
////                for(int k = 0; k < _fan.collectedSongLists()[i].size();k++)
////                    cout << (_fan.collectedSongLists()[i].at(k)).toStdString() << endl;
//            }
//            //关注用户信息
//            const Json::Value arrayObj2 = resultRoot["attentedUsers"];
//            for (unsigned int i = 0; i < arrayObj2.size(); i++)
//            {
//                Json::Value value;
//                value = arrayObj2[i];

//                QList<QString> ret;
//                ret.append(QString::fromStdString(value["name"].asString()));
//                ret.append(QString::fromStdString(value["password"].asString()));
//                ret.append(QString::fromStdString(value["label"].asString()));
//                ret.append(QString::fromStdString(value["sex"].asString()));
//                ret.append(QString::fromStdString(value["birthday"].asString()));
//                ret.append(QString::fromStdString(value["address"].asString()));
//                ret.append(QString::fromStdString(value["icon"].asString()));

//                _fan.addAttentedUsers(QString::fromStdString(value["name"].asString()),ret);
////                for(int k = 0; k < _fan.attentedUsers()[i].size();k++)
////                    cout << (_fan.attentedUsers()[i].at(k)).toStdString() << endl;
//            }
//            //粉丝信息
//            const Json::Value arrayObj3 = resultRoot["fanUsers"];
//            for (unsigned int i = 0; i < arrayObj3.size(); i++)
//            {
//                Json::Value value;
//                value = arrayObj3[i];

//                QList<QString> ret;
//                ret.append(QString::fromStdString(value["name"].asString()));
//                ret.append(QString::fromStdString(value["password"].asString()));
//                ret.append(QString::fromStdString(value["label"].asString()));
//                ret.append(QString::fromStdString(value["sex"].asString()));
//                ret.append(QString::fromStdString(value["birthday"].asString()));
//                ret.append(QString::fromStdString(value["address"].asString()));
//                ret.append(QString::fromStdString(value["icon"].asString()));

//                _fan.addFanUsers(QString::fromStdString(value["name"].asString()),ret);
////                for(int k = 0; k < _fan.fanUsers()[i].size();k++)
////                    cout << (_fan.fanUsers()[i].at(k)).toStdString() << endl;
//            }
////            if(_songlistNames.size() != 0)
////                emit createdSongListsChanged();
//            for (unsigned int i = 0; i < _songlistNames.size(); i++)
//            {
//                cout << _songlistNames.at(i).toStdString() << endl;
//            }
//        }
//    }
//}


//void FanProxy::myRegister(QString username, QString userpw)
//{
//    Json::Value root;
//    root["type"] = "REGISTER";
//    root["userName"] = username.toStdString();
//    root["userPassword"] = userpw.toStdString();
//    root.toStyledString();
//    std::string out = root.toStyledString();

//    auto s = out.data();
//    boost::system::error_code ec;
//    sock.write_some(buffer(s,strlen(s)),ec);
//    if(ec)
//    {
//        std::cout << boost::system::system_error(ec).what() << std::endl;
//        return;
//    }
//    std::cout<<"send message to server: " <<out<<endl;

//    //读取服务器返回的消息：是否注册成功
//    char data[512];
//    memset(data,0,sizeof(char)*512);//reset 0 to data[]
//    while(strlen(data)==0){
//        sock.read_some(buffer(data),ec);
//    }
//    if(ec)
//    {
//        std::cout << boost::system::system_error(ec).what() << std::endl;
//        return;

//    }
//    cout << "receive from server : " << data<<endl;
//    Json::Reader reader;
//    Json::Value resultRoot;
//    if(!reader.parse(data, resultRoot)){
//        std::cout << "json received faild" <<std::endl;
//        return;
//    }else {
//        string ret = resultRoot["registerSuccess"].asString();
//        m_result = QString::fromStdString(ret);
//        cout << "register " << ret<<endl;
//        emit resultChanged();
//        return;

//    }
//}
