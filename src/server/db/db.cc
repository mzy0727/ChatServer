#include "db.h"
#include <muduo/base/Logging.h>

// 数据库配置信息
static string server = "127.0.0.1";
static string user = "root";
static string password = "123456";
static string dbname = "chat";

// 初始化数据库连接
MySQL::MySQL(MYSQL **conn, Connection_Pool *connPool)
{
   *conn = connPool->get_connection();
   _connRAII = *conn;
   _poolRAII = connPool;
}

// 释放数据库连接资源
MySQL::~MySQL()
{
    _poolRAII->release_connection(_connRAII);
}

// // 连接数据库
// bool MySQL::connect()
// {
//     MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
//                                   password.c_str(), dbname.c_str(), 3306, nullptr, 0);
//     if (p != nullptr)
//     {
//         // C和C++代码默认的编码字符是ASCII，如果不设置，从MySQL上拉下来的中文显示？
//         mysql_query(_conn, "set names gbk");
//         LOG_INFO << "connect mysql success!";
//     }
//     else
//     {
//         LOG_INFO << "connect mysql fail!";
//     }

//     return p;
// }

// 更新操作
bool MySQL::update(string sql)
{
    // 从数据库连接池取一个连接
 //   MYSQL *mysql = nullptr;
   // ConnectionRAII mysqlcon(&mysql, connPool);
    if (mysql_query(_connRAII, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "更新失败!";
        return false;
    }

    return true;
}

// 查询操作
MYSQL_RES *MySQL::query(string sql)
{
    if (mysql_query(_connRAII, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "查询失败!";
        return nullptr;
    }
    
    return mysql_use_result(_connRAII);
}

// 获取连接
MYSQL* MySQL::getConnection()
{
    return _connRAII;
}