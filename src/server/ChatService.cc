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

}
void ChatService::login(const TcpConnectionPtr& conn, json &js, Timestamp time){
    // LOG_INFO<<"do login service!";
    int id = js["id"];
    string pwd = js["password"];

    User user = _userModel.query(id);
    if(user.getId() == id && user.getPwd() == pwd){
        if(user.getState() == "online"){
            //已经登录
            json responce;
            responce["msgid"] = LOGIN_MSG_ACK;
            responce["errno"] = -2;
            responce["errmsg"] = "该账号已经登录";
            conn->send(responce.dump());
        }else{
             // 登录成功
            {
                lock_guard<mutex> lock(_connMutex);
                _userConnMap.insert({id,conn});
            }
            user.setState("online");
            _userModel.updateState(user);

            json responce;
            responce["msgid"] = LOGIN_MSG_ACK;
            responce["errno"] = 0;
            responce["id"] = user.getId();
            responce["name"] = user.getName();
            
            // 查询该用户是否有离线消息
            vector<string> offlinemsgs = _offlineMsgModel.query(id);
            if(!offlinemsgs.empty()){
                responce["offlinemsg"] = offlinemsgs;
                // 读取该用户的离线消息后，把用户的离线消息清除
                _offlineMsgModel.remove(id);
            }

            conn->send(responce.dump());
        }
        
    }else{
        json responce;
        responce["msgid"] = LOGIN_MSG_ACK;
        responce["errno"] = -1;
        responce["errmsg"] = "用户不存在或者密码错误";
        conn->send(responce.dump());
    }
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
        json responce;
        responce["msgid"] = REG_MSG_ACK;
        responce["errno"] = 0;
        responce["id"] = user.getId();
        conn->send(responce.dump());
   }else{
        json responce;
        responce["msgid"] = REG_MSG_ACK;
        responce["errno"] = -1;
        conn->send(responce.dump());
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
