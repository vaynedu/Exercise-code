/*******************************************************************
*    > F-Name :  yue_se_fu_huan.c
*    > Author :  vaynedu
*    > E-mail :  1219345363@qq.com
*    > C-time :  Fri 19 Jul 2019 10:18:00 PM CST
*******************************************************************/


/*
 * 越是简单的问题就应该花心思去思考，追求极致，会更优秀
 *
 * 哪种实现起来更简单？时间复杂度各是多少？
 * 如果数据量大的情况，哪个更能经得住考验？
 * 如果考虑实际情况，哪一个会更好呢？
 *
 *
 * */

/*
 * 问题描述：编号为 1-N 的 N 个士兵围坐在一起形成一个圆圈，从编号为 1 的士兵开始依次报数（1，2，3...这样依次报），
 * 数到 m 的 士兵会被杀死出列，之后的士兵再从 1 开始报数。直到最后剩下一士兵，求这个士兵的编号。
 *
 * 这到题目有三种解法
 *
 * 1. 数组
 * 2. 链表
 * 3. 递归
 *
 * 备注：没有考虑异常边界情况，最重要的思路
 *
 * */


#include<stdio.h>

#include<stdlib.h> // for malloc/free

void ysfh_array(int *a, int n, int m)
{
	int i = 0;
	int j = 0;
	int cnt = 0;
	int idx = 0;

	while(1)
	{
		for(i = j; i < n; i++)
		{
			if(a[i] != -1)
			{
				cnt++;
			}

			if(cnt == m)
			{
			   printf("idx = %d, %d\n", ++idx, a[i]);
			   a[i] = -1;
			   j = (i + 1) % n;
			   cnt = 0;
			   break;
			}

		}

		if(i == n)
		{
			j = 0;
		}

		/* last people*/
		if(idx == n -1)
		{
			for(i = 0; i < n; i++)
			{
				if(a[i] != -1)
				{
				   printf("idx = %d, %d\n", ++idx, a[i]);
				}
			}

			break;
		}

	}



}

/*
 * 使用链表实现约瑟夫环
 *
 * */

typedef struct ds_list_s ds_list_t;

struct ds_list_s
{
  int data;     
  ds_list_t  *next;
};	

ds_list_t  *init_ysfh_list(int *a, int n)
{
	ds_list_t *head = NULL;
	ds_list_t *cur = NULL;
    ds_list_t *tail = NULL;;

    head = (ds_list_t*)malloc(sizeof(ds_list_t));
	head->data = a[0];
	head->next = NULL;

	tail = head;

	int i;
	for(i = 1; i < n; i++)
	{	
    	cur = (ds_list_t*)malloc(sizeof(ds_list_t));
		cur->data = a[i];
		cur->next = NULL;

		tail->next = cur;
		tail = tail->next;

	}

	tail->next = head;

	return head;

}

void ysfh_list(int *a, int n, int m)
{
	ds_list_t *head = init_ysfh_list(a, n);
	ds_list_t *cur = NULL;


	int idx = 0;
	int cnt = 1;

    while(head->next != head)
	{
	    if(cnt == m - 1)
		{
		   cur = head->next;
		   printf("idx:%d %d\n", ++idx, cur->data);
		   
		   head->next = cur->next;
		   free(cur);
		   cnt = 0;

		}
		
		cnt++;
		head = head->next;
	}

    printf("idx:%d %d\n", ++idx, head->data);
    free(head);	
}



int ysfh_recursive(int n, int m)
{
    if(n == 1)
    {
        return 1;
    }

    return (ysfh_recursive(n-1, m) + m - 1) % n + 1;
}

 

int main()
{
    int n = 5;
	int m = 3;
	int a[5] = {0};


	int i = 0;

    for(i = 0; i < n; i++)
	{
		a[i] = i + 1;
	}
    
    // ysfh_array(a, n, m);

    // ysfh_list(a, n, m);

    printf("%d\n", ysfh_recursive(n, m));



	return 0;
}


