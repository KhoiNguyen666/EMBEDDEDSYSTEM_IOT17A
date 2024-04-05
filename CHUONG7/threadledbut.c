#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>
#define ON 1
#define OFF 0
int led_fd, button_fd; // device file
/* Bien luu thoi gian delay */
static int t = 1000; //don vi la milisecond, ban dau mac dinh la 1000 ms
/* Ham sleep ms su dung usleep cua linux */
void sleepms(int ms)
{
//usleep in us, sleep in second
usleep(1000*ms); //convert to microseconds
return;
};
void* btn_polling(void* param);
int main(int argc, char** agrv)
{
/*Bien cau truc chua tham so se truyen cho ham xu ly cua thread
*/
const char *thread_parms = "button thread";
pthread_t thread_id; // thread
int led_no; //So hieu led 0-4
//Mang chua gia tri trang thai 6 button se doc
char buttons[6] = {'0', '0', '0', '0', '0', '0'};
int i;
//Mo thiet bi (led port), can kiem tra chinh xac ten trong /dev
led_fd = open("/dev/leds", 0);
if (led_fd < 0)
{
perror("open device leds");
exit(1);
}
else printf("open device led ok\n");
//Mo thiet bi (button port)
button_fd = open("/dev/buttons", 0); //mo button port
if(button_fd < 0)
{
perror("open device buttons");
exit(1);
}
else printf("open device button ok\n");
thread_id = pthread_create(&thread_id, NULL, &btn_polling, (void
*)thread_parms);
//Ban dau tat ca cac led deu off
for(i=0;i<4;i++) ioctl(led_fd, OFF, i);
led_no=0;
while(1)
{
//Bat led led_no
ioctl(led_fd, ON, led_no);
//Sleep in t ms
sleepms(t);
//Tat led led_no va chuan bi bat luon led ke tiep
ioctl(led_fd, OFF, led_no);
led_no++;
if(led_no == 4) led_no = 0;
}
close(button_fd);
close(led_fd);
return 0;
}
void* btn_polling(void* param)
{
/*const char thread_parms* = "button thread";*/
char cur_btn[2], old_btn[2] = {'0', '0'};
int i;
/*Lien tuc tham do trang thai nut bam (K1, K2 co duoc an)*/
for(;;)
{
int num=read(button_fd, cur_btn, sizeof(cur_btn));
if(num != sizeof(cur_btn))
{
perror("read buttons:");
exit(1);
}
//Chi can doc K1, K2 tuong ung voi tang/giam led speed
//Doc K1
if(old_btn[0] != cur_btn[0])
{
sleepms(300);//delay de phim nay len
old_btn[0] = cur_btn[0];
t = t+50; //tang thoi gian delay
printf("K1 is pressed/released t = %dms\n",t);
}
//Doc K2
if(old_btn[1] != cur_btn[1])
{
sleepms(300); //delay de phim nay len
old_btn[1] = cur_btn[1];
t = t-50; //giam thoi gian delay
if(t < 100) t = 100;
printf("K2 is pressed/released t = %dms\n",t);
}
}
}
