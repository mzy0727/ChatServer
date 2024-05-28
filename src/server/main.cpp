#include "ChatServer.h"
#include <iostream>
using namespace std;
int main()
{
    EventLoop loop;
    InetAddress listenAddr(8888);
    // Create a ChatServer object
    ChatServer server(&loop, listenAddr,"ChatServer");
    // Start the server
    server.start();

    // 开启事件循环
    loop.loop();
    return 0;
}
