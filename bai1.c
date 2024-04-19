#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ON	1
#define OFF	0

int main(int argc, char **argv)
{
	int fd;
	char key = 0xff;
	int status_led[4] = {0, 0, 0, 0};

	// Mở LED device
	fd = open("/dev/leds", 0);
	if (fd < 0)
	{
		perror("open device leds");
		exit(1);
	}
	
	// Mac dinh cho 4 led tat
	ioctl(fd, OFF, 0);
	ioctl(fd, OFF, 1);
	ioctl(fd, OFF, 2);
	ioctl(fd, OFF, 3);
	
	printf( "Nhan phim '1' 1 LED sang\n" );
	printf( "Nhan phim '2' 2 LED sang\n" );
	printf( "Nhan phim '3' 3 LED sang\n" );
	printf( "Nhan phim '4' 4 LED sang\n" );

	while(1)
	{
		key = getchar();
		sleep(1);
		
		switch(key) 
		{
		case '1':
			printf("1 LED sang\n");
			ioctl(fd, ON, 0);
			ioctl(fd, OFF, 1);
			ioctl(fd, OFF, 2);
			ioctl(fd, OFF, 3);
			break;
		case '2':
			printf("2 LED sang\n");
			ioctl(fd, ON, 0);
			ioctl(fd, ON, 1);
			ioctl(fd, OFF, 2);
			ioctl(fd, OFF, 3);
			break;
		case '3':
			printf("3 LED sang\n");
			ioctl(fd, ON, 0);
			ioctl(fd, ON, 1);
			ioctl(fd, ON, 2);
			ioctl(fd, OFF, 3);	
			break;
		case '4':
			printf("4 LED sang\n");
			ioctl(fd, ON, 0);
			ioctl(fd, ON, 1);
			ioctl(fd, ON, 2);
			ioctl(fd, ON, 3);	
			break;
		}
	}	
			
	close(fd);
	return 0;
}
