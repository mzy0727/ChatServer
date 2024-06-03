#include "Use_db.h"

Use_DB::Use_DB(string url,string user, string password, string databaseName, int sql_num)
    :m_url(url),
    m_user(user),
    m_passWord(password),
    m_databaseName(databaseName),
    m_sql_num(sql_num)
{
     
    // 数据库连接池初始化
    _connPool->get_instance();
    _connPool->init(m_url, m_user,m_passWord,m_databaseName, 3306, m_sql_num);
}

Connection_Pool* Use_DB::get_Connection_Pool(){
    return _connPool;
}