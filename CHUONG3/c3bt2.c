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
int main(int argc, char** argv)
{
	 int fd; 
	 fd = open("/dev/leds", 0); 
	 if (fd < 0) 
	 { 
		 perror("open device leds"); 
		 exit(1); 
	 }
	
	int buttons_fd;
	char buttons[6] = {'0', '0', '0', '0', '0', '0'};//Mảng lưu trạng thái của 6 nút bấm
	buttons_fd = open("/dev/buttons", 0); //Mở file
	if (buttons_fd < 0) //Kiểm tra quá trình mở file
	{
		perror("open device buttons");
		exit(1);
	}

 ioctl(fd, OFF, 0); 
 ioctl(fd, OFF, 1);
 ioctl(fd, OFF, 2);
 ioctl(fd, OFF, 3);

	while(1)
	//Hỏi vòng kiểm tra trạng thái các nút bấm
	{
		char current_buttons[6];
		int count_of_changed_key;
		int i;
		//Đọc trạng thái các nút bấm
		if (read(buttons_fd, current_buttons, sizeof current_buttons) != sizeof current_buttons)
		{
			perror("read buttons:");
			exit(1);
		}
		//Kiểm tra trạng thái các nút bấm và in ra trạng thái phù hợp (Key up hay Key down)
		for (i = 0, count_of_changed_key = 0; i < sizeof buttons / sizeof
		buttons[0]; i++)
		{
			if (buttons[i] != current_buttons[i])
			{
				buttons[i] = current_buttons[i];
				printf("%skey %d is %s", count_of_changed_key? ", ": "",
				i+1, buttons[i] == '0' ? "up" : "down");

				if (i+1 == 1) 
				{
					if(buttons[i] == '1')
					{ioctl(fd, ON, 0);}
					else ioctl(fd, OFF, 0);
				}
				if (i+1 == 2) 
				{
					if(buttons[i] == '1')
					{ioctl(fd, ON, 1);}
					else ioctl(fd, OFF, 1);
				}
				if (i+1 == 3) 
				{
					if(buttons[i] == '1')
					{ioctl(fd, ON, 2);}
					else ioctl(fd, OFF, 2);
				}
				if (i+1 == 4) 
				{
					if(buttons[i] == '1')
					{ioctl(fd, ON, 3);}
					else ioctl(fd, OFF, 3);
				}

				count_of_changed_key++;
			}
		}
		if (count_of_changed_key) {
				printf("\n");
		}
	}
	close(buttons_fd); //Đóng file thiết bị
	return 0;
}
