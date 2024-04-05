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
void set_buzzer_freq(int fd, int freq)
{
	// this IOCTL command is the key to set frequency
	int ret = ioctl(fd, 1, freq);
	if(ret < 0)
	{
		perror("set the frequency of the buzzer");
		exit(1);
	}
}

int fd, button_fd, step = 0, freq = 1000 ; // device file
fd = open("/dev/pwm", 0);
if (fd < 0)
{
	perror("open pwm_buzzer device");
	exit(1);
}	
set_buzzer_freq(fd, freq);
printf( "\tFreq = %d\n", freq );

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
//Mang chua gia tri trang thai 6 button se doc
char buttons[6] = {'0', '0', '0', '0', '0', '0'};
int i;
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
freq = freq+50; //tang thoi gian delay
if(freq >1000) freq = 1000;
set_buzzer_freq(fd, freq);
printf("K1 is pressed/released freq = %dHz\n",t);
}
//Doc K2
if(old_btn[1] != cur_btn[1])
{
sleepms(300); //delay de phim nay len
old_btn[1] = cur_btn[1];
freq = freq-50; //giam thoi gian delay
if(freq < 50) freq = 50;
set_buzzer_freq(fd, freq);
printf("K2 is pressed/released freq = %dHz\n",t);
}
}
}
