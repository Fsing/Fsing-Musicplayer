#ifndef FANBROKER_H
#define FANBROKER_H
#include "ralationbroker.h"
#include "user.h"
#include "fan.h"
#include <memory>

class FanBroker : public RalationBroker
{
public:
    static FanBroker *getInstance();   //静态成员函数，只能通过类名调用
//    void findFanByName();
//    void getNext();
//    void selectAll();
//    void addFan();
//    void selectFan();
private:
    FanBroker();        //保护构造函数，不能通过new创建对象
    ~FanBroker();
    static FanBroker *_instance;
    std::map<std::string, std::shared_ptr<User>> _fans;
};
#endif // FANBROKER_H
