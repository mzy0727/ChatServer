#pragma once

#include "sql_connection_pool.h"

#include <mysql/mysql.h>

#include <string>
using namespace std;

// 资源获取即初始化
// 数据库操作类
class MySQL
{
public:
    // 初始化数据库连接
    MySQL(MYSQL **conn, Connection_Pool *connPool);
    // 释放数据库连接资源
    ~MySQL();
    // // 连接数据库
    // bool connect();
    // 更新操作
    bool update(string sql);
    // 查询操作
    MYSQL_RES *query(string sql);
    // 获取连接
    MYSQL* getConnection();
private:
    MYSQL *_connRAII;
    Connection_Pool *_poolRAII;

};

