#include <stdio.h>
#include <pthread.h>//khai bao cac ham xu ly tuyen
/*Ham thuc thi tuyen*/
void* do_loop(void* data)
{int i;
for(i=0;i<10;i++)
{
sleep(1);//Dung 1 s
printf("Thread '%d'-Got '%d'\n",data,i);
}
pthread_exit(NULL);//Cham dut tuyen
}
int main(void)
{
pthread_t p_thread;
int thr_id;
int a=1;
int b=2;
/*Tao tuyen*/
thr_id=pthread_create(&p_thread, NULL, do_loop,(void*)a);
do_loop((void*)b);
return 0;
}
