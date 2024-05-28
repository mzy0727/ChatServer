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
    LOG_INFO<<"do login service!";
}
void ChatService::reg(const TcpConnectionPtr& conn, json &js, Timestamp time){
    LOG_INFO<<"do reg service!";
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
