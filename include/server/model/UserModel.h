#pragma once

#include "User.h"
#include "db.h"
#include "Use_db.h"

// User表的数据操作类
class UserModel{

public:
    UserModel();
    // User表的增加方法
    bool insert(User &user);
    // 根据用户号码查询用户信息
    User query(int id);
    // 更新用户的状态信息
    bool updateState(User user);
    // 重置用户的状态信息
    void resetState();
private:
    MySQL *mysqlconn;
};
