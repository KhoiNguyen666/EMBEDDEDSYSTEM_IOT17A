#include <stdlib.h> 
#include <unistd.h> 
#include <sys/ioctl.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#define ON 1 
#define OFF 0 
int main(int argc, char **argv) 
{ 
 int fd,i=0; 
 fd = open("/dev/leds", 0); 
 if (fd < 0) 
 { 
 perror("open device leds"); 
 exit(1); 
 } 
 while(1) 
 { 
	for(;;) 
	{
		if(i>=4) {i=0; break;}
		ioctl(fd, ON, i);
		i++;
	}
	 usleep(250000); 
	for(;;) 
	{
		if(i>=4) {i=0; break;}
		ioctl(fd, OFF, i);
		i++;
	}
	 usleep(250000);  
 } 
 close(fd); 
 return 0; 
}
