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
 int fd,i; 
 fd = open("/dev/leds", 0); 
 if (fd < 0) 
 { 
 perror("open device leds"); 
 exit(1); 
 } 
 while(1) 
 { 
	i=0;
	do {ioctl(fd, ON, i);i++;} while(i<4);
	 usleep(250000); 
	i=0;
	do {ioctl(fd, OFF, i);i++;} while(i<4);
	 usleep(250000);  
 } 
 close(fd); 
 return 0; 
}
