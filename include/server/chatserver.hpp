#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;

class ChatServer
{
private:
    TcpServer _server;
    EventLoop *_loop;
    void onConnection(const TcpConnectionPtr &conn);
    void onMessage(const TcpConnectionPtr &conn,
                   Buffer *buffer,
                   Timestamp time);

public:
    ChatServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const string &nmaeArg);
    void start();
};

#endif