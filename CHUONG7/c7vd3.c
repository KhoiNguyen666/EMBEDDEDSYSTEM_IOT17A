#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
char message[]="Hello World";
void *do_thread(void *data)
{
printf("Thread function is executing....\n");
printf("Thread data is %s ",(char*)message);
sleep(3);
strcpy(message, "Bye!"); //copy gia tri chuoi tay phai vao chuoi tay trai
pthread_exit("Thank you for using my thread\n"); // gia tri tra ve cua thread khi ket thuc
}
int main() //Chuong trinh chinh
{
int res;
pthread_t a_thread;//khai bao bien voi kieu pthread thi moi chay duoc
void *thread_result;
/*Tao va thuc thi tuyen*/
res=pthread_create(&a_thread,NULL,do_thread,(void*)message);
if(res!=0)
{
perror("Thread created error");
exit(EXIT_FAILURE);
}
/*Doi tuyen ket thuc*/
printf("Waiting for thread to finish...\n");
res=pthread_join(a_thread,&thread_result);
if(res!=0)
{
perror("Thread wait error");
exit(EXIT_FAILURE);
}
/*In ket qua tra ve cua tuyen*/
printf("Thread completed, it returned %s\n",(char*) thread_result);
printf("Message is now %s\n",message);
return 0;
}
