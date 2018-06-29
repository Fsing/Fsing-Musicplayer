#ifndef RELATIONBROKER_H
#define RELATIONBROKER_H
#include <mysql/mysql.h>
class Connection;

class RelationBroker
{
public:
    RelationBroker();

private:
    MYSQL m_database;
}
