#ifndef FANBROKER_H
#define FANBROKER_H
class RelationBroker;
class vector;
class Fan;

class FanBroker : public RelationBroker
{
public:
    static FanBroker *Instance();
    void findFanByName();
    void getNext();
    void selectAll();
    void addFan();
    void selectFan();

private:
    FanBroker();

    static FanBroker *m_instance;
    vector<Fan*> _fans;
};

#endif // FANBROKER_H
