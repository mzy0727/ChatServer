#pragma once
#include "db.h"
#include "sql_connection_pool.h"
#include<string>

class Use_DB{

public:
    Use_DB(string url,string user, string password, string databaseName, int sql_num);
    ~Use_DB();
    Connection_Pool* get_Connection_Pool();
private:
     // 基本配置
    string m_url;
    string m_user;          // 登陆数据库用户名
    string m_passWord;      // 登陆数据库密码
    string m_databaseName;  // 数据库名
    int m_sql_num;          // 数据库池连接数
    // 数据库连接池对象
    Connection_Pool *_connPool;

};