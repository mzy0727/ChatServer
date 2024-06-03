#include "OfflineMsgModel.h"
#include "db.h"


OfflineMsgModel::OfflineMsgModel(){
    MYSQL *mysql = nullptr;
     Use_DB *useDB = new Use_DB("127.0.0.1", "root", "123456", "chat", 10);
     mysqlconn = new MySQL(&mysql,useDB->get_Connection_Pool());
}
 // 存储用户的离线消息
void OfflineMsgModel::insert(int userid, string msg){
    char sql[1024] = {0};
    sprintf(sql,"insert into offlinemessage values(%d,'%s')",userid,msg.c_str());

   // MySQL mysql;
    if(mysqlconn){
        mysqlconn->update(sql);
    }
}

// 删除用户的离线消息
void OfflineMsgModel::remove(int userid){
    char sql[1024] = {0};
    sprintf(sql,"delete from offlinemessage where userid = %d",userid);

 //   MySQL mysql;
    if(mysqlconn){
        mysqlconn->update(sql);
    }
}

// 查询用户的离线消息
vector<string> OfflineMsgModel::query(int userid){
    char sql[1024] = {0};
    sprintf(sql,"select message from offlinemessage where userid = %d",userid);
   // MySQL mysql;
    vector<string> vec;
    if(mysqlconn){
        MYSQL_RES *res = mysqlconn->query(sql);
        if(res != nullptr){
            // 把userid用户的所有离线消息放入vec中返回
            MYSQL_ROW row;
            while((row = mysql_fetch_row(res)) != nullptr){
                vec.push_back(row[0]);
            }
            mysql_free_result(res);
            return vec;
        }
    }
    return vec;
}