#pragma once
#include <tiny_network/net/EventLoop.h>
#include <tiny_network/net/TcpServer.h>
#include <tiny_network/logger/Logging.h>
#include <string>
#include <iostream>
 using namespace std;
// using namespace tiny_network;
// using namespace tiny_network::net;
// using namespace tiny_network::logger;

class ChatServer{
public:
    // 初始化聊天服务器
    ChatServer(EventLoop* loop, const InetAddress& addr, const std::string& name);
    // 启动服务
    void start();

       
private:
    // 上报连接相关信息的回调函数
    void onConnection(const TcpConnectionPtr&);
    // 上报读写事件相关信息的回调函数
    void onMessage(const TcpConnectionPtr&, Buffer*, Timestamp);

    EventLoop *_loop;
    TcpServer _server;
};