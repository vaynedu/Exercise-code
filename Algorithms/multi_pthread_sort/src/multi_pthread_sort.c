#include <apue.h>

#define NUMMAX   100000000
#define M4OT     100000 //mission for one thread
#define CPUS     4

int *parr   = NULL;
int  thnums = 0;
int  nummax = NUMMAX;
pthread_t   *thid;

typedef struct th_in {
    int *addr;
    int  low;
    int  high;
} _thin;

typedef struct th_merge {
    int *addr;
    int  mg1;
    int  len1;
    int  mg2;
    int len2;
} _thmerge;


void init(int ac,char **av,int **parr)
{
    int loop = 0,*arr;
    int cpus = CPUS;
    if(NULL == parr){
        return ;
    }
    if(1 < ac){
        nummax = atoi(av[1]);
        if(1 >= nummax){
            return;
        }
    }
    arr = malloc(sizeof(int)*nummax);
    *parr = arr;
    if(NULL == arr){
        return;
        *parr = NULL;
    }
    srand(time(0));
    for(loop=0;loop<nummax;++loop){
        arr[loop] = rand()%nummax;
    }
    if(CPUS >= cpus){
        thnums = 2*cpus;
    }else{
        thnums = cpus;
    }
    thnums = thnums > (nummax/M4OT)?(nummax/M4OT):thnums ;
    //The thnums should be a 2^n (0<n && 32>n)
    if(1 >= thnums){
        //zero
        thnums = 2;
    }else if(thnums & (thnums-1)){
        //not a 2^n
        if(thnums & (0x01 << 30)){
             thnums = 0x01 << 30;
        }else{
            loop = 0;
            for(loop=29;loop>=0;--loop){
                if(thnums & (0x01 << loop)){
                    thnums = 0x01 << (loop + 1);
                    break;
                }
            }
        }
    }
   // printf("thnums:%d\n",thnums);
    thid = malloc(sizeof(pthread_t)*thnums);
}

void quick_sort(int *addr,int low,int high)
{
    int  povit  = addr[low];
    int  lowpos = low , highpos = high - 1;

    if(NULL == addr || lowpos >= highpos){
        return;
    }
    while(lowpos < highpos){
        while((lowpos < highpos) && (addr[highpos] >= povit)){
            highpos--;
        }
        if(lowpos < highpos){
            addr[lowpos] = addr[highpos];
            lowpos++;
        }
        while((lowpos < highpos) && (addr[lowpos] <= povit)){
            lowpos++;
        }
        if(lowpos < highpos){
            addr[highpos] = addr[lowpos];
            highpos--;
        }
    }
    addr[lowpos] = povit;
    quick_sort(addr,low,lowpos);
    quick_sort(addr,lowpos+1,high);
    return;
}

void *thread_quik(void *pos)
{
    int i = 0;
    _thin mypos;
    memcpy((void *)&mypos,pos,sizeof(_thin));
    quick_sort(mypos.addr,mypos.low,mypos.high);


   // for(i = mypos.low; i < mypos.high;i++){
   //       printf("%d ",mypos.addr[i]);
   // }
   //  printf("\n");
    pthread_exit(NULL);
    return NULL;
}

void * thread_merge(void *pos)
{
    _thmerge mymg;
    int p1,p2,loop;
    int p1max,p2max,loopmax;
    int *addr;
    memcpy((void *)&mymg,pos,sizeof(_thmerge));
   // printf(">>>>>>>>>>>> %d,%d,%d,%d\n",mymg.mg1,mymg.len1,mymg.mg2,mymg.len2);

    loopmax = mymg.len1+mymg.len2;
    addr = malloc(sizeof(int)*loopmax);
    if(NULL == addr){
        return NULL;
    }
    p1=mymg.mg1,p2=mymg.mg2;
    p1max=mymg.mg1+mymg.len1;
    p2max=mymg.mg2+mymg.len2;
    for(loop=0;loop<loopmax && p1<p1max && p2<p2max;++loop){
        if(mymg.addr[p1] > mymg.addr[p2]){
            addr[loop] = mymg.addr[p2];
            ++p2;
        }else{
            addr[loop] = mymg.addr[p1];
            ++p1;
        }
    }
   // printf("<> %d,%d\n",mymg.mg1,loopmax);
    if(p1 == p1max){
        memcpy(&addr[loop],&mymg.addr[p2],sizeof(int)*(p2max-p2));
    }else{
        memcpy(&addr[loop],&mymg.addr[p1],sizeof(int)*(p1max-p1));
    }
    memcpy(&mymg.addr[mymg.mg1],addr,sizeof(int)*loopmax);
#if 0
    printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
    for(loop=0;loop<loopmax;++loop){
        printf("%d ",addr[loop]);
    }
    printf("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n");
#endif

    free(addr);
    pthread_exit(NULL);
    return NULL;
}

int main(int ac,char **av)
{
    int       loop = 0;
    _thin    *tharg;
    _thmerge *thmg;
    int       unit , factor;
    int       prntpos ,index;
    int       gap  =  2;


    double user_time = 0.0;
    clock_t start = 0;
    clock_t end = 0;


    start = clock();

    init(ac,av,&parr);
    if(NULL == parr){
        return -1;
    }
    factor = thnums;
    prntpos = rand()%nummax;
    unit = nummax/thnums;
    tharg = malloc(sizeof(_thin)*thnums);
    thmg  = malloc(sizeof(_thmerge)*thnums);
    for(loop=0;loop<thnums;++loop){
        tharg[loop].addr = parr;
        tharg[loop].low  = loop * unit;
        tharg[loop].high = tharg[loop].low + unit + (loop/(thnums-1))*(nummax-thnums*unit);
        if(pthread_create(&thid[loop],NULL,thread_quik,(void *)&tharg[loop])){
        //error
        }
    }
    for(loop=0;loop<thnums;++loop){
        pthread_join(thid[loop],NULL);
    }

    /*-------------------------------------------------------*/
    gap = 2;
    while(gap <= thnums){
        //for(loop=0,index=0;loop<thnums,index<thnums/2;loop+=gap,index++){
        for(loop=0;loop<thnums;loop+=gap){
            thmg[loop].addr = parr;
            thmg[loop].mg1  = tharg[loop].low;
            thmg[loop].len1 = tharg[loop + gap/2 - 1].high - tharg[loop].low;
            thmg[loop].mg2  = tharg[loop + gap/2].low;
            thmg[loop].len2 = tharg[loop + gap - 1].high - tharg[loop + gap/2].low ;
            if(pthread_create(&thid[loop],NULL,thread_merge,(void *)&thmg[loop])){
            //error
            }
        }
        for(index=0;index<thnums;index+=gap){
            pthread_join(thid[index],NULL);
        }

        gap *= 2;
    }//end while
    /*-------------------------------------------------------*/
    //print out

   // printf("+++++++++++++++++++++++++++++++++\n");
   // for(loop=prntpos;loop<prntpos+20 && loop<nummax;++loop){
   //    printf("%d ",parr[loop]);
   // }
   // printf("\n+++++++++++++++++++++++++++++++++\n");

   end = clock();
   user_time = ((double)end-start)/CLOCKS_PER_SEC;

   printf("user_time = %lf\n",user_time);
    return 0;
}
