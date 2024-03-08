#include <stdlib.h> 
#include <unistd.h> 
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#define ON 1 
#define OFF 0 
void ledtat()
{
 int fd;
 fd = open("/dev/leds", 0); 
 if (fd < 0) 
 { 
 perror("open device leds"); 
 exit(1); 
 } 
 ioctl(fd, OFF, 0); 
 ioctl(fd, OFF, 1);
 ioctl(fd, OFF, 2);
 ioctl(fd, OFF, 3);
}
int main(int argc, char **argv) 
{ 
 int fd,i,temp,n; 
 int led[4];
 fd = open("/dev/leds", 0); 
 if (fd < 0) 
 { 
 perror("open device leds"); 
 exit(1); 
 } 
ledtat();
 while(1) 
 { 
	for(i=0;i<16;i++)
	{	
		temp=i;
		for(n=0;temp>0;n++)
		{
			led[n]=temp%2;
			temp=temp/2;
			
		}
		for(n=0;n<4;n++)
		{
			ioctl(fd, led[n], n);
		}
		usleep(300000);
	}
 } 
 close(fd); 
 return 0; 
}
