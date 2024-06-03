#pragma once

#include "User.h"
#include "db.h"
#include "Use_db.h"

// 群组用户，多了一个role角色信息，从User类直接继承，复用User的其它信息
class GroupUser : public User
{
public:
    void setRole(string role) { this->role = role; }
    string getRole() { return this->role; }
  //  GroupUser();
private:
    string role;
private:
  //  MySQL *mysqlconn;
};

