#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <sys/time.h>


using namespace std;



uint32_t get_now_time()
{
  volatile uint32_t  now = time(0);
  return now;
}

inline uint32_t get_now_time_1()
{
   struct timeval tv;
   
   gettimeofday(&tv, NULL); // #include<sys/time.h>
   
  return (uint32_t)tv.tv_sec;
}


uint64_t get_tick()
{
   struct timeval tv;
   
   gettimeofday(&tv, NULL);
   
   return ((uint64_t)tv.tv_sec) * 100000ULL + tv.tv_usec / 10;
}

uint64_t get_ms_now_time()
{
   volatile uint64_t ms_now = get_tick() / 100;
   
   return ms_now;
}


inline uint64_t get_ms_now_time_1()
{
   struct timeval tv;
   
   gettimeofday(&tv, NULL); // #include<sys/time.h>
   
   uint64_t  tick = ((uint64_t)tv.tv_sec) * 100000ULL + tv.tv_usec / 10;
   
   uint64_t ms_now = tick / 100;
   
   return ms_now;
}


int main(void)
{
 

    cout << "time(0):" << time(0) << endl;

    cout << "get_now_time():" << get_now_time() << endl;
   
    cout << "get_now_time_1():" << get_now_time_1() << endl;

    cout << "get_tick():" << get_tick() << endl;
   
    cout << "get_ms_now_time():" << get_ms_now_time() << endl;
    
    cout << "get_ms_now_time_1():" << get_ms_now_time_1() << endl;


    return 0;
}







