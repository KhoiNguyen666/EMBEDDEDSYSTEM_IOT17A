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
#include <string.h>


void led_off(int fd_led)
{
	 ioctl(fd_led, 0, 0); 
	 ioctl(fd_led, 0, 1);
	 ioctl(fd_led, 0, 2);
	 ioctl(fd_led, 0, 3);
}
void led_on(int fd_led)
{
	 ioctl(fd_led, 1, 0); 
	 ioctl(fd_led, 1, 1);
	 ioctl(fd_led, 1, 2);
	 ioctl(fd_led, 1, 3);
}
void ledled(int a, int fd_led)
{
	int i;
	if(a<5)
	{
		for(i=0;i<a;i++) ioctl(fd_led, 1, i);
	}
}


int main(int argc, char** argv)
{
	int buttons_fd;
	char buttons[6] = {'0', '0', '0', '0', '0', '0'};//Mảng lưu trạng thái của 6 nút bấm
	buttons_fd = open("/dev/buttons", 0); //Mở file
	if (buttons_fd < 0) //Kiểm tra quá trình mở file
	{
		perror("open device buttons");
		exit(1);
	}
	 

	 int fd_led;
	 fd_led = open("/dev/leds", 0); 
	 if (fd_led < 0) 
	 { 
	 perror("open device leds"); 
	 exit(1); 
	 } 
		int fd;
		fd = open("/dev/pwm", 0);
		if (fd < 0)
		{
			perror("open pwm_buzzer device");
			exit(1);
		}

     FILE * pFile; 
     int n,k;
	 char c, mystring[100], text[]="aaaaaaaaaa", text2[]="chao cac ban"; 
	         
	         pFile = fopen ("test.txt","w"); 
        	 if (pFile!=NULL) 
        	 { 
            	 fwrite(text, sizeof(text), 1, pFile);
            	 fclose (pFile); 
        	 }


 
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
				/*printf("%skey %d is %s", count_of_changed_key? ", ": "",
				i+1, buttons[i] == '0' ? "up" : "down");*/

				if (i == 0) 
				{
					if(buttons[i] == '0')
					{
						pFile = fopen ("test.txt" , "r"); 
							if (pFile != NULL)
							{ 
								if ( fgets (mystring , 100 , pFile) != NULL ) 
								puts (mystring); 
								fclose (pFile); 
							}
					}

				}
				if (i == 1) 
				{
					if(buttons[i] == '0')
					{ 
						 pFile = fopen ("test.txt","w"); 
						 if (pFile!=NULL) 
						 { 
						     fseek(pFile, SEEK_SET, 0);
					    	 fwrite(text2, sizeof(text2), 1, pFile);
					    	 fclose (pFile); 
						 }
					
					}
				}
				if (i == 2) 
				{
					if(buttons[i] == '0')
					{
					    printf("nhap n: ");
					    scanf("%d", &n);
					    ledled(n,fd_led);
				     		for(k=0;k<n;k++)
				    		{
							if(n==5) led_on(fd_led);
							ioctl(fd, 1, 1000);
							/*printf( "\tLan %d Freq = %d\n",k+1 ,1000 );*/
							usleep(500000);
							/*printf( "\tLan %d Freq = %d\n",k+1 ,0 );*/
							ioctl(fd, 0);
							if(n==5) led_off(fd_led);
							usleep(500000);
				    		}
				    		led_off(fd_led);
					}					
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

