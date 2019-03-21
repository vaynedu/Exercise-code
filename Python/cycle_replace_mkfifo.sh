#! /bin/bash

idx=0

while true
do
  if (( $idx > 15 ))
  then
      echo "end" 
      break
  fi
  cnt=`echo $idx | awk '{printf "%02d", $1}'`
  echo $cnt
  let idx++
  
  cat download_suc_file.log  | grep 2019_03_17_$cnt | head -n 12 > 2019_03_17.txt.100 && cat 2019_03_17.txt.100

  cat 2019_03_17.txt.100 | while read sLine
  do
       # python check_two_ip_ds_deal_log.py  $sLine &
        echo $sLine
  done


  while true
  do
       run_num=`ps -uax | grep check_two_ip_ds_deal_log.py -c`
       if [ $rum_num == 1 ];then
             sleep 5
             break
       fi
   
       sleep 20
 
  done


done
