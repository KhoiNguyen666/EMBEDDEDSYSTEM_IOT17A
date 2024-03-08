#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define ON 1 
#define OFF 0 
int main(int argc, char **argv)
{
int fd,i; 
	 fd = open("/dev/leds", 0); 
	 if (fd < 0) 
	 { 
		 perror("open device leds"); 
		 exit(1); 
	 }
char key = 0xff;
while( 1 )
{
 ioctl(fd, OFF, 0); 
 ioctl(fd, OFF, 1);
 ioctl(fd, OFF, 2);
 ioctl(fd, OFF, 3);
int led_states[4]={0,0,0,0};
key = getchar();
printf("key:%d\n",key);
sleep(1);
switch(key)
{
	case('1'):
	{
		for(i=0;i<4;i++)
 		{ioctl(fd, ON, i); 
 		usleep(300000); 
		ioctl(fd, OFF, i);}
		break;
	}  
	case('2'):
	{
		for(i=0;i<4;i++)
 		{ioctl(fd, ON, i);} 
 		usleep(300000); 
		for(i=0;i<4;i++)
 		{ioctl(fd, OFF, i);}
 		usleep(300000); 
		break;
	} 
	case('3'):
	{
		exit(1);
		break;
	}
	default:
	printf("key:%d invalid\n",key);
}

}
}
