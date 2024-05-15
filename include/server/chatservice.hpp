#ifndef CHATSERVICE_H
#define CHATSERVICE_H
#include <functional>
#include <usermodel.hpp>
#include <unordered_map>
#include <muduo/net/TcpConnection.h>
#include "json.hpp"
#include <mutex>
#include "groupmodel.hpp"
#include "friendmodel.hpp"
#include "offlinemessagemodel.hpp"
#include "redis.hpp"
using json = nlohmann::json;
using namespace muduo::net;
using namespace muduo;
using namespace std;
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;
class ChatService
{
private:
    unordered_map<int, MsgHandler> _msgHandlerMap;
    ChatService();
    unordered_map<int, TcpConnectionPtr> _userConnMap;
    mutex _connMutex;
    UserModel _userModel;
    OfflineMsgModel _offlineMsgModel;
    FriendModel _friendModel;
    GroupModel _groupModel;

    Redis _redis;

public:
    static ChatService *instance();
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    MsgHandler getHandler(int msgid);
    void clientCloseException(const TcpConnectionPtr &conn);
    void oneChat(const TcpConnectionPtr &coon, json &js, Timestamp time);
    void reset();
    void addFriend(const TcpConnectionPtr &coon, json &js, Timestamp time);
    void createGroup(const TcpConnectionPtr &coon, json &js, Timestamp time);
    void groupChat(const TcpConnectionPtr &coon, json &js, Timestamp time);
    void addGroup(const TcpConnectionPtr &coon, json &js, Timestamp time);
    void handleRedisSubscribeMessage(int userid, string msg);
};

#endif