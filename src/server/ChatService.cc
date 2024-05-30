#include "ChatService.h"
#include "public.h"
#include <tiny_network/logger/Logging.h>
#include<vector>
using namespace std;

ChatService* ChatService::instance(){
    static ChatService service;
    return &service;
}
// 注册消息以及对应的Handeler回调操作
ChatService::ChatService(){
    _msgHandlerMap.insert({LOGIN_MSG,std::bind(&ChatService::login,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    _msgHandlerMap.insert({REG_MSG,std::bind(&ChatService::reg,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    _msgHandlerMap.insert({ONE_CHAT_MSG,std::bind(&ChatService::oneChat,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    _msgHandlerMap.insert({ADD_FRIEND_MSG, std::bind(&ChatService::addFriend, this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});

    // 群组业务管理相关事件处理回调注册
    _msgHandlerMap.insert({CREATE_GROUP_MSG, std::bind(&ChatService::createGroup, this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    _msgHandlerMap.insert({ADD_GROUP_MSG, std::bind(&ChatService::addGroup, this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    _msgHandlerMap.insert({GROUP_CHAT_MSG, std::bind(&ChatService::groupChat, this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});

}
void ChatService::login(const TcpConnectionPtr& conn, json &js, Timestamp time){
    // LOG_INFO<<"do login service!";
    int id = js["id"];
    string pwd = js["password"];

    User user = _userModel.query(id);
    if(user.getId() == id && user.getPwd() == pwd){
        if(user.getState() == "online"){
            //已经登录
            json response;
            response["msgid"] = LOGIN_MSG_ACK;
            response["errno"] = -2;
            response["errmsg"] = "该账号已经登录";
            conn->send(response.dump());
        }else{
             // 登录成功
            {
                lock_guard<mutex> lock(_connMutex);
                _userConnMap.insert({id,conn});
            }
            user.setState("online");
            _userModel.updateState(user);

            json response;
            response["msgid"] = LOGIN_MSG_ACK;
            response["errno"] = 0;
            response["id"] = user.getId();
            response["name"] = user.getName();
            
            // 查询该用户是否有离线消息
            vector<string> offlinemsgs = _offlineMsgModel.query(id);
            if(!offlinemsgs.empty()){
                response["offlinemsg"] = offlinemsgs;
                // 读取该用户的离线消息后，把用户的离线消息清除
                _offlineMsgModel.remove(id);
            }

            // 查询该用户的好友信息并返回
            vector<User> userVec = _friendModel.query(id);
            if (!userVec.empty())
            {
                vector<string> vec2;
                for (User &user : userVec)
                {
                    json js;
                    js["id"] = user.getId();
                    js["name"] = user.getName();
                    js["state"] = user.getState();
                    vec2.push_back(js.dump());
                }
                response["friends"] = vec2;
            }

            // 查询用户的群组信息
            vector<Group> groupuserVec = _groupModel.queryGroups(id);
            if (!groupuserVec.empty())
            {
                // group:[{groupid:[xxx, xxx, xxx, xxx]}]
                vector<string> groupV;
                for (Group &group : groupuserVec)
                {
                    json grpjson;
                    grpjson["id"] = group.getId();
                    grpjson["groupname"] = group.getName();
                    grpjson["groupdesc"] = group.getDesc();
                    vector<string> userV;
                    for (GroupUser &user : group.getUsers())
                    {
                        json js;
                        js["id"] = user.getId();
                        js["name"] = user.getName();
                        js["state"] = user.getState();
                        js["role"] = user.getRole();
                        userV.push_back(js.dump());
                    }
                    grpjson["users"] = userV;
                    groupV.push_back(grpjson.dump());
                }

                response["groups"] = groupV;
            }

            conn->send(response.dump());
        }
        
    }else{
        json response;
        response["msgid"] = LOGIN_MSG_ACK;
        response["errno"] = -1;
        response["errmsg"] = "用户不存在或者密码错误";
        conn->send(response.dump());
    }
}

// 处理注销业务
void ChatService::loginout(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int userid = js["id"].get<int>();

    {
        lock_guard<mutex> lock(_connMutex);
        auto it = _userConnMap.find(userid);
        if (it != _userConnMap.end())
        {
            _userConnMap.erase(it);
        }
    }

    // 用户注销，相当于就是下线，在redis中取消订阅通道
  //  _redis.unsubscribe(userid); 

    // 更新用户的状态信息
    User user(userid, "", "", "offline");
    _userModel.updateState(user);
}

// 处理注册业务
void ChatService::reg(const TcpConnectionPtr& conn, json &js, Timestamp time){
   // LOG_INFO<<"do reg service!";
   string name = js["name"];
   string pwd = js["password"];

   User user;
   user.setName(name);
   user.setPwd(pwd);
   bool state = _userModel.insert(user);
   if(state){
        // 注册成功
        json response;
        response["msgid"] = REG_MSG_ACK;
        response["errno"] = 0;
        response["id"] = user.getId();
        conn->send(response.dump());
   }else{
        json response;
        response["msgid"] = REG_MSG_ACK;
        response["errno"] = -1;
        conn->send(response.dump());
   }
}
// 处理客户端异常退出
void ChatService::clientCloseException(const TcpConnectionPtr& conn){
    User user;
    {
        lock_guard<mutex> lock(_connMutex);
        for(auto it = _userConnMap.begin(); it != _userConnMap.end(); ++it){
            if(it->second == conn){
                // 从map表删除用户的连接信息
                user.setId(it->first);
                _userConnMap.erase(it);
                break;
            }
        }
    }
    if(user.getId() != -1){
        user.setState("offline");
        _userModel.updateState(user);
    }
}
// 点对点聊天业务
void ChatService::oneChat(const TcpConnectionPtr& conn, json &js, Timestamp time){
    int toid = js["to"].get<int>();

    {
        lock_guard<mutex> lock(_connMutex);
        auto it = _userConnMap.find(toid);
        if(it != _userConnMap.end()){
            // toid在线，转发消息   服务器主动推送消息给toid用户
            it->second->send(js.dump());
            return ;
            
        }
            
                
    }
    //toid不在线，存储离线消息
    _offlineMsgModel.insert(toid,js.dump());
    
}


// 添加好友业务 msgid id friendid
void ChatService::addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int userid = js["id"].get<int>();
    int friendid = js["friendid"].get<int>();

    // 存储好友信息
    _friendModel.insert(userid, friendid);
}

// 创建群组业务
void ChatService::createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int userid = js["id"].get<int>();
    string name = js["groupname"];
    string desc = js["groupdesc"];

    // 存储新创建的群组信息
    Group group(-1, name, desc);
    if (_groupModel.createGroup(group))
    {
        // 存储群组创建人信息
        _groupModel.addGroup(userid, group.getId(), "creator");
    }
}

// 加入群组业务
void ChatService::addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int userid = js["id"].get<int>();
    int groupid = js["groupid"].get<int>();
    _groupModel.addGroup(userid, groupid, "normal");
}

// 群组聊天业务
void ChatService::groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    int userid = js["id"].get<int>();
    int groupid = js["groupid"].get<int>();
    vector<int> useridVec = _groupModel.queryGroupUsers(userid, groupid);

    lock_guard<mutex> lock(_connMutex);
    for (int id : useridVec)
    {
        auto it = _userConnMap.find(id);
        if (it != _userConnMap.end())
        {
            // 转发群消息
            it->second->send(js.dump());
        }
        else
        {
            // 存储离线群消息
            _offlineMsgModel.insert(id, js.dump());
            // // 查询toid是否在线 
            // User user = _userModel.query(id);
            // if (user.getState() == "online")
            // {
            //     _redis.publish(id, js.dump());
                
            // }
            // else
            // {
            //     // 存储离线群消息
            //     _offlineMsgModel.insert(id, js.dump());
            // }
        }
    }
}


// 服务器异常，业务重置方法
void ChatService::reset(){
    // 把online状态用户，设置为offline
    _userModel.resetState();
}

MsgHandler ChatService::getHandler(int msgid){
    auto it = _msgHandlerMap.find(msgid);
    if(it == _msgHandlerMap.end()){
        return [=](const TcpConnectionPtr& conn, json &js, Timestamp time){
            LOG_ERROR << "msgid:" << msgid <<" can not find handler!";
        };      
    }else{
         return _msgHandlerMap.at(msgid);
    }
   
}
