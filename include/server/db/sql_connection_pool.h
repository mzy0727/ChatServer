#pragma once

#include<mysql/mysql.h>
#include<string>
#include<iostream>
#include<mutex>
#include<semaphore.h>
#include<list>
#include<atomic>
using namespace std;

class Connection_Pool{
public:
    static Connection_Pool* get_instance(){
        static Connection_Pool connPool;
        return &connPool;
    }
    void init(string url, string user, string password, string database_name,int port,int max_conn);
    MYSQL* get_connection();
    bool release_connection(MYSQL *conn);
    int get_freeconn();

private:
    Connection_Pool();
    ~Connection_Pool();
    string m_url;
    string m_port;
    string m_user;
    string m_password;
    string m_database_name;

    int m_max_conn; // 最大连接数
    int m_cur_conn; // 当前已使用连接数
    int m_free_conn;    // 当前空闲连接数
    mutex m_mutex;   // 互斥锁
    list<MYSQL*> conn_list; // 连接池
    sem_t reserve;  //信号量 指示是否有空闲连接

};

// // 资源获取即初始化
// class ConnectionRAII{
// public:
//     ConnectionRAII(MYSQL **conn,Connection_Pool *connPool);
//     ~ConnectionRAII();
// private:
//     MYSQL *connRAII;
//     Connection_Pool *poolRAII;
// };