#include "ChatServer.h"

ChatServer:: ChatServer(EventLoop* loop, const InetAddress& addr, const std::string& name)
    : _server(loop,addr,name),
      _loop(loop)
{
    // 注册连接回调
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));
    // 注册消息回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    // 设置线程数量
    _server.setThreadNum(4);
}

void ChatServer::start()
{
    _server.start();
}

void ChatServer::onConnection(const TcpConnectionPtr& conn)
{
    if (conn->connected())
    {
        LOG_INFO << "Connection UP : " << conn->peerAddress().toIpPort().c_str();
    }
    else
    {
        LOG_INFO << "Connection DOWN : " << conn->peerAddress().toIpPort().c_str();
    }
}

void ChatServer::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
    std::string msg = buf->retrieveAllAsString();
    LOG_INFO << conn->name() << " echo " << msg.size() << " bytes, "
             << "data received at " << time.toFormattedString();
    conn->send(msg);
}