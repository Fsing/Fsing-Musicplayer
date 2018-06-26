#include <iostream>
#include <mysql/mysql.h>    //用的是c++的API
#include <cstring>
#include <algorithm>
#include <string>
#include <database.h>
#include <sstream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "database.h"
#include "fsingservice.h"

using namespace std;
using namespace boost::asio;
using boost::asio::io_service;

//typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

//void client_session(socket_ptr sock)
//{
//    auto ep = sock->remote_endpoint();//获得客户端的连接端口
//    std::cout<<ep.address().to_string()<<"连接"<<std::endl;

//    //    string data;
//    boost::system::error_code ec;
//    //    size_t len;

//    while(true)
//    {
//        char data[512];
//        DatabaseController database;
//        /* len =*/ sock->read_some(buffer(data), ec);
//        if(ec)
//        {
//            std::cout << boost::system::system_error(ec).what() << std::endl;
//            break;
//        }
//        string str = data;
//        int sig = str.find(',');
//        cout << sig << endl;
//        string pw{str.begin() +sig+1,str.end()};
//        string name{str.begin(),str.begin() + sig};
//        cout << name << "," << pw << endl;
//        //        std::copy(str.begin() + 4,str.end(),pw);
//        auto ret = database.myRegister(name,pw);

//        char data1[512];
//        data1[0] = '1';
//        sock->write_some(buffer(data1), ec);  //客户输入的消息，重新写到客户端
//        if(ec)
//        {
//            std::cout << boost::system::system_error(ec).what() << std::endl;
//            break;
//        }
//    }

//    std::cout<<ep.address().to_string()<<"关闭"<<std::endl;
//}

int main()
{
    Server server;
    server.connect();

//    io_service service;   //创建调度器
//    ip::tcp::endpoint ep(ip::tcp::v4(),2001);  //监听端口
//    ip::tcp::acceptor acc(service,ep); //创建连接器

//    while(true){
//        socket_ptr sock(new ip::tcp::socket(service));
//        acc.accept(*sock); //接收新的连接
//        boost::thread(boost::bind(client_session,sock)); //开辟线程去处理该连接上的事务
//        //前两步可以等价于
//        //        acc.async_accept(*sock,boost::bind(client_session,sock));
//    }
    return 0;
}
