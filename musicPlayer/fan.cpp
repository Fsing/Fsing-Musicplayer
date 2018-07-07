#include "fan.h"

Fan::Fan(QString name, QString password, QString label, QString sex, QString birthday, QString address, QString icon):m_name{name},m_password{password},m_label{label},m_sex{sex},m_birthday{birthday},m_address{address},m_icon{icon}
{

}

//getting
QList<QList<QString> > Fan::createdSongLists()
{
    return _createdSongList;
}

QList<QList<QString> > Fan::collectedSongLists()
{
    return _collectedSongList;
}

QList<QList<QString> > Fan::attentedUsers()
{
    return _attentedUsers;
}

QList<QList<QString> > Fan::fanUsers()
{
    return _fanUsers;
}

QString Fan::username(){
    return m_name;
}

QString Fan::password(){
    return m_password;
}

QString Fan::label(){
    return m_label;
}

QString Fan::sex(){
    return m_sex;
}

QString Fan::birthday(){
    return m_birthday;
}

QString Fan::address(){
    return m_address;
}

QString Fan::icon(){
    return m_icon;
}


//setting
void Fan::setUsername(QString username){
    m_name= username;
}

void Fan::setPassword(QString password){
    m_password = password;
}

void Fan::setLabel(QString label){
    m_label = label;
}

void Fan::setSex(QString sex){
    m_sex = sex;
}

void Fan::setBirthday(QString birthday){
    m_birthday = birthday;
}

void Fan::setAddress(QString address){
    m_address = address;
}

void Fan::setIcon(QString icon){
    m_icon = icon;
}


//adding
//void Fan::addAttentedUsers(Fan attentedUsers)
//{
//    _attentedUsers.append(attentedUsers);
//}

//void Fan::addFanUsers(Fan fanUsers)
//{
//    _fanUsers.append(fanUsers);
//}

//void Fan::addCollectedSongLists(SongList collectedSongList)
//{
//    _collectedSongList.append(collectedSongList);
//}

//void Fan::addCreatedSongLists(SongList createdSongList)
//{
//    _createdSongList.append(createdSongList);
//}

//void Fan::deleteAttentedUsers(Fan attentedUsers)
//{
//    if(!_attentedUsers.isEmpty()){
//        auto i = _attentedUsers.indexOf(attentedUsers);
//        _attentedUsers.removeAt(i);
//    }
//}

//void Fan::deleteFanUsers(Fan fanUsers)
//{
//    if(!_fanUsers.isEmpty()){
//        auto i = _fanUsers.indexOf(fanUsers);
//        _fanUsers.removeAt(i);
//    }
//}

//void Fan::deleteCollectedSongLists(SongList collectedSongList)
//{
//    if(!_collectedSongList.isEmpty()){
//        auto i = _collectedSongList.indexOf(collectedSongList);
//        _collectedSongList.removeAt(i);
//    }
//}

//void Fan::deleteCreatedSongLists(SongList createdSongList)
//{
//    if(!_createdSongList.isEmpty()){
//        auto i = _createdSongList.indexOf(createdSongList);
//        _createdSongList.removeAt(i);
//    }
//}

//
