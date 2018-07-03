#ifndef FANBROKER_H
#define FANBROKER_H
#include "ralationbroker.h"
#include "fan.h"
#include <memory>
#include <map>

class FanBroker : public RalationBroker
{
public:
    static std::shared_ptr<FanBroker> getInstance();   //静态成员函数，只能通过类名调用
    std::shared_ptr<Fan> findUser(std::string username);            //在缓存中查询
    std::shared_ptr<Fan> retrievalUser(std::string username);       //在数据库中检索,检索用户的所有信息，包括歌单、关注、粉丝
private:
    FanBroker();        //保护构造函数，不能通过new创建对象
//    ~FanBroker();
    static std::shared_ptr<FanBroker> _instance;
    std::map<std::string, std::shared_ptr<Fan>> _fans;       //用户名为键
};
#endif // FANBROKER_H
