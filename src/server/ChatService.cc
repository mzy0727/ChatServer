#include "ChatService.h"
#include "public.h"
#include <tiny_network/logger/Logging.h>


ChatService* ChatService::instance(){
    static ChatService service;
    return &service;
}
// 注册消息以及对应的Handeler回调操作
ChatService::ChatService(){
    _msgHandlerMap.insert({LOGIN_MSG,std::bind(&ChatService::login,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    _msgHandlerMap.insert({REG_MSG,std::bind(&ChatService::reg,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});

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
            user.setState("online");
            _userModel.updateState(user);

            json responce;
            responce["msgid"] = LOGIN_MSG_ACK;
            responce["errno"] = 0;
            responce["id"] = user.getId();
            responce["name"] = user.getName();
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
