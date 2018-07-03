#include "fanproxy.h"
#include <json/json.h>
#include <iostream>
#include "fanbroker.h"

using std::cout;        using std::endl;

std::string FanProxy::myLogin(std::string username, std::string password)
{
    cout <<"enter Mylogin" << endl;
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
