#include "fsingservice.h"
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "database.h"
#include "macro.h"

using namespace boost::asio;
using std::cout;            using std::endl;
using std::string;          using std::vector;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;


io_service service;   //创建调度器
ip::tcp::endpoint ep(ip::tcp::v4(),2001);  //监听端口
ip::tcp::acceptor acc(service,ep); //创建连接器
DatabaseController database;

//拆分来自客户端的消息
vector<string> splitToString(char data[]);
//接受客户端传来的请求事务,并将结果返回给客户端
void receiveMessage(socket_ptr sock);
//返回处理信息给客户端
void dealResult(socket_ptr sock);


Server::Server()
{
}

void Server::connect()
{
    //如果套接字连接一个已经在使用中的本地地址，则进行重用地址，因为每一个连接都由本地地址和远端地址的组合唯一确定，所以只要远端地址不同，两个套接口与一个地址捆绑并无大碍
    //设置套接口实现不要因为一个地址已被一个套接口使用就不让它与另一个套接口捆绑，在bind()调用前先设置SO_REUSEADDR选项
//    ip::tcp::socket sock_;
    bool value = true;
    setsockopt(1,SOL_SOCKET,SO_REUSEADDR,(void *)&value,sizeof(value));
    while(true){
        socket_ptr sock(new ip::tcp::socket(service));
        acc.accept(*sock); //接收新的连接
        boost::thread(boost::bind(receiveMessage,sock)); //开辟线程去处理该连接上的事务
        //前两步可以等价于
        //        acc.async_accept(*sock,boost::bind(client_session,sock));
    }
}

string Server::dealMessage(string sig,vector<string> str)
{
    string res;
    if(sig == LOGIN){//请求登录
        res =database.myLogin(str[1],str[2]);
    }else if(sig == REGISTER){//请求注册
        res = database.myRegister(str[1],str[2]);
    }else if(sig == ADD_CREATESONGLIST){//创建新歌单

    }else if(sig == ADD_ATTENTION){//添加关注好友

    }else if(sig == ADD_COLLECTIONSONGLIST){//添加收藏歌单

    }else if(sig == ADD_BEATTENTION){//添加粉丝

    }else if(sig == ADD_SONG){//添加歌曲（只有原创歌单才能添加歌曲）

    }else if(sig == DELETE_ATTENTION){//取消关注

    }else if(sig == DELETE_BEATTENTION){//减少粉丝

    }
    return res;
}

//接受客户端传来的请求事务,并将结果返回给客户端
void receiveMessage(socket_ptr sock)
{
    //    auto ep = sock->remote_endpoint();//获得客户端的连接端口
    boost::system::error_code ec;
    auto ep1 = sock->remote_endpoint(ec); //获得客户端的连接端口
    if(ec)
    {
        std::cout << "fslfkjsfl" << boost::system::system_error(ec).what() << std::endl;
    }
    std::cout<<ep1.address().to_string()<<"连接"<<std::endl;

    Server service;
    while(true)
    {
        char data1[512];
        DatabaseController database;
        /*auto len = */sock->read_some(buffer(data1), ec);
        if(ec)
        {
            std::cout << boost::system::system_error(ec).what() << std::endl;
            break;
        }
        auto result1 = splitToString(data1);
        auto result2 = service.dealMessage(result1[0],result1);

        //写回客户端
        char data2[512];
        result2.copy(data2,result2.size(),0);
        sock->write_some(buffer(data2), ec);  //客户输入的消息，重新写到客户端
        if(ec)
        {
            std::cout << boost::system::system_error(ec).what() << std::endl;
            break;
        }
    }
    std::cout<<ep1.address().to_string()<<"关闭"<<std::endl;
}
vector<string> splitToString(char data[])
{
    string str = data;
    vector<string> ret;
    auto l = find(str.begin(),str.end(),',');
    string tmp{str.begin(),l};
    ret.push_back(tmp);
    auto i = l;
    while((l != str.end()) && ((l = find(++i,str.end(),','))  <= str.end())){
        tmp = {i,l};
        i = l;
        ret.push_back(tmp);
    }
    return ret;
}

void dealResult(socket_ptr sock)
{

}
