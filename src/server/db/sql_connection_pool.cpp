#include "sql_connection_pool.h"

Connection_Pool::Connection_Pool(){
    m_cur_conn = 0;
    m_free_conn = 0;
}
Connection_Pool::~Connection_Pool(){
    list<MYSQL*>::iterator iter;
    for(iter = conn_list.begin(); iter != conn_list.end(); ++iter){
        MYSQL * conn = *iter;
        mysql_close(conn);
    }
}


// 初始化连接池
void Connection_Pool::init(string url, string user, string password, string database_name,int port,int max_conn){
    m_url = url;
    m_port = port;
    m_user = user;
    m_password = password;
    m_database_name = database_name;
    // 构造连接
    for(int i = 0; i < max_conn; ++i){
        // 初始化一个mysql连接的实例对象，MYSQL* mysql_init(MYSQL *mysql);
        MYSQL *conn = nullptr;
        conn = mysql_init(conn);
        if(conn == nullptr){
           // LOG_ERROR("MySQL init Error");
            exit(1);
        }

        // 与数据库引擎建立连接
 //       MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
//                                   password.c_str(), dbname.c_str(), 3306, nullptr, 0);
        conn = mysql_real_connect(conn,"127.0.0.1","root","123456","chat",3306,nullptr,0);
        // conn = mysql_real_connect(conn,url.c_str(),user.c_str(),password.c_str(),database_name.c_str(),port,nullptr,0);
        if(conn == nullptr){
            // LOG_ERROR("MySQL real connect Error");
            exit(1);
        }

        // 添加到连接链表
        conn_list.push_back(conn);
        ++m_free_conn;
    }
    {
        sem_init(&reserve,0,m_free_conn);
        lock_guard<mutex> lock(m_mutex);
        m_max_conn = m_free_conn;
    }
   

}


// 有请求时，从数据库连接池返回一个可用连接
MYSQL* Connection_Pool::get_connection(){
    // 无空闲连接
    if(conn_list.size() == 0){
        return nullptr;
    }
    MYSQL *conn = nullptr;
    // 等待空闲连接
    sem_wait(&reserve);
    // 加互斥锁
    {
        lock_guard<mutex> lock(m_mutex);
        // 取连接池第一个连接
        conn = conn_list.front();
        conn_list.pop_front();

        --m_free_conn;
        ++m_cur_conn;
    }
    
  
    return conn;
}

// 释放当前使用的连接，成功返回true
bool Connection_Pool::release_connection(MYSQL *conn){
    if(conn == nullptr){
        return false;
    }
    {
        lock_guard<mutex> lock(m_mutex);
        conn_list.push_back(conn);
        ++m_free_conn;
        --m_cur_conn;
    }
  

    sem_post(&reserve);
    return true;
}

// 当前空闲连接数
int Connection_Pool::get_freeconn(){
    return this->m_free_conn;
}

// ConnectionRAII::ConnectionRAII(MYSQL **conn,Connection_Pool *connPool){
//     *conn = connPool->get_connection();
//     connRAII = *conn;
//     poolRAII = connPool;
// }
// ConnectionRAII::~ConnectionRAII(){
//     poolRAII->release_connection(connRAII);
// }