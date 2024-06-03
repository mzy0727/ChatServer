#include "FriendModel.h"


FriendModel::FriendModel(){
     MYSQL *mysql = nullptr;
     Use_DB *useDB = new Use_DB("127.0.0.1", "root", "123456", "chat", 10);
     mysqlconn = new MySQL(&mysql,useDB->get_Connection_Pool());
}
// 添加好友关系
void FriendModel::insert(int userid, int friendid)
{
    // 1.组装sql语句
    char sql[1024] = {0};
    sprintf(sql, "insert into friend values(%d, %d)", userid, friendid);

    
     mysqlconn->update(sql);
    // if (mysql.connect())
    // {
    //     mysql.update(sql);
    // }
}

// 返回用户好友列表
vector<User> FriendModel::query(int userid)
{
    // 1.组装sql语句
    char sql[1024] = {0};

    sprintf(sql, "select a.id,a.name,a.state from user a inner join friend b on b.friendid = a.id where b.userid=%d", userid);

    vector<User> vec;
   // MySQL mysql;
   if (mysqlconn != nullptr)
   {
        MYSQL_RES *res =mysqlconn->query(sql);
        if (res != nullptr)
        {
            // 把userid用户的所有离线消息放入vec中返回
            MYSQL_ROW row;
            while((row = mysql_fetch_row(res)) != nullptr)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                vec.push_back(user);
            }
            mysql_free_result(res);
            return vec;
        }
    }
    return vec;
}