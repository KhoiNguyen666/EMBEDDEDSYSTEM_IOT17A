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
 int fd; 
 int i;
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
 while(1) 
 { 
  for(i = 0; i<4; i++)
  {
	ioctl(fd, ON, i);   
	usleep(500000);
	ioctl(fd, OFF, i);
  }

 } 
 close(fd); 
 return 0; 
}
