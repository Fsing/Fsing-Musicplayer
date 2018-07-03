#ifndef FANPROXY_H
#define FANPROXY_H

//#include "fanbroker.h"
#include <memory>
#include <string>
#include "songlistbroker.h"

using std::string;

class FanProxy
{
public:
    //用户登录
    string myLogin(string username,string password);
private:
};
#endif // FANPROXY_H
