#pragma once

enum EnMsgType{
    LOGIN_MSG = 1,  // 登录消息
    LOGIN_MSG_ACK,  // 登录回复消息
    REG_MSG,        // 注册消息
    REG_MSG_ACK,
    ONE_CHAT_MSG,   // 聊天消息
};