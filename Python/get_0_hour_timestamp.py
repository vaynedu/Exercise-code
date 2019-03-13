#! /bin/bash

import time

#cal time
g_date = []
g_date_timestamp = []

#get now date
now_time=time.time()
g_date.append(time.strftime('%Y%m%d', time.localtime(now_time)))
g_date.append(time.strftime('%Y%m%d', time.localtime(now_time - 24*3600)))

#get 0:0:0 timestamp
today_time_stamp=int(time.mktime(time.strptime(time.strftime('%Y-%m-%d 00:00:00',time.localtime(now_time)),'%Y-%m-%d %H:%M:%S')))

g_date_timestamp.append(today_time_stamp+24*3600-1)
g_date_timestamp.append(today_time_stamp)
g_date_timestamp.append(today_time_stamp-1)
g_date_timestamp.append(today_time_stamp-24*3600)




print g_date
print g_date_timestamp
