#! /usr/local/bin/python3

# coding:utf-8
import json
import os
import time
import sys
import MySQLdb
import uuid


def global_val():
    global g_db
    global g_conn
    global g_date



def connect_mysql_db():
    global g_db
    global g_conn

    try: # table name : test_20200910
        g_db = MySQLdb.connect(db = 'xxxxxxxx',
                               host = 'xxxxxxxxxxx.com',
                               user = 'root',
                               passwd = 'xxxxxxxxxxxxxxxx',
                               port = 3306)
    except MySQLdb.Error as  e:
        #logger.error("connect mysql failed !!! Mysql Error %d: %s" % (e.args[0], e.args[1]))
        print("connect mysql failed !!! Mysql Error %d: %s" % (e.args[0], e.args[1]))
        sys.exit()
    else:
        #print "connect mysql success!!!"
        g_conn = g_db.cursor()

def convert(value):
    if isinstance(value, (str, uuid.UUID)):
        return f'"{value}"' #fstring
    return str(value)

def write_mysql_db(batch_res, all_line_num):

    now_time=time.time()
    date = time.strftime('%Y%m%d', time.localtime(now_time)) #20200910

    db_name =  'test_' + date #db_name = test_20200910
    predix_sql = 'insert into ' + db_name + '(time_stamp,uuid,url,range_num,range_size,ip_num,platform_id,layer,name,status,info) values '
    post_fix = ''

    
    idx = 0
    cnt = 0
    sql = ""
    global_sql = ""
    for key in batch_res.keys():
        value = batch_res[key]
        sql += '(' + str(value[0])
        for i in range(1,len(value)):
            sql += ',' + convert(value[i])
        sql += '),'


        idx += 1
        if idx >= 10:
           global_sql = predix_sql + sql[0:-1] + post_fix
           exec_mysql_db(date,global_sql, all_line_num,idx) 
           #print(global_sql)
           # reinit     
           global_sql = ""
           sql = ""
           idx = 0
           cnt = 0
     
    if idx > 0 :
        global_sql = predix_sql + sql[0:-1] + post_fix
        exec_mysql_db(date,global_sql, all_line_num,idx)    
        #print(global_sql)

    


def exec_mysql_db(date, global_sql, all_line_num, sql_len):

     global g_conn
    
     cnt = 0  
     while True:
        if cnt > 10:
            break
        try:
           t1 = time.time()
           g_conn.execute(global_sql)
           t2 = time.time()

           print("date: %s insert %d, mysql cost time: %d" %(date,sql_len,int(t2-t1)))
           break
        except MySQLdb.Error as e:
           print("time: %d  Mysql Error %d: %s,  all line:%d, all sql:%d" % (cnt, e.args[0], e.args[1],all_line_num, sql_len))
           cnt += 1
           time.sleep(2)




def close_mysql_db():
    global g_db
    g_db.close()


def main():

    url = 'http://test.com/1.mp4'
    range_num = 10
    range_size = 1
    ip_num = 10
    platform_id = 200111
    layer = 0
    name = "test"
    status = 0
    info = '0'


    batch_res = {}
    for i in range(1,99):
        time_stamp = int(time.time())
        uuid_str = uuid.uuid1()
        batch_res[uuid_str] = [time_stamp, uuid_str,  url, range_num, range_size, ip_num, platform_id, layer, name, status, info]


    all_line_num = 99
    write_mysql_db(batch_res, all_line_num)


if __name__ == '__main__':
    connect_mysql_db()
    main()
    close_mysql_db()

