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
	 

	 int fd;
	 fd = open("/dev/leds", 0); 
	 if (fd < 0) 
	 { 
	 perror("open device leds"); 
	 exit(1); 
	 } 
	 ioctl(fd, 0, 0); 
	 ioctl(fd, 0, 1);
	 ioctl(fd, 0, 2);
	 ioctl(fd, 0, 3);




	 FILE * pFile; 
	 char mystring[100], text[22]="so lan nhan key 1 la: ";
	 int k=0;
 
	while(1)
	//Hỏi vòng kiểm tra trạng thái các nút bấm
	{

		char current_buttons[6];
		int count_of_changed_key;
		int i;

		int cur,n,ntam=0,l, led[4];		

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

				if (i == 0) 
				{
					if(buttons[i] == '0')
					{
					n=0;
					 pFile = fopen ("input.txt","r"); 
					 if (pFile!=NULL) 
					 {do 
					     { 
					     k = fgetc (pFile); 
					     if (k == 'a') n++; 
					     } while (k != EOF); 
					     fclose (pFile);
					     printf("So lan xuat hien chu a la: %d \n", n);  
					 }
					ntam=n%16;
					for (l = 0; l < 4; l++)
					{
					    led[l] = (ntam >> l)&1;
					    ioctl(fd, led[l], l);
					}
					}

				}
				if (i == 1) 
				{
					if(buttons[i] == '0')
					{ 
					cur=0;
					pFile = fopen ("input.txt" , "r+"); 
					 if (pFile!=NULL) 
					 {do 
					     { 
					     k = fgetc (pFile); 
					     if (k == 'a') k = k-32; 
					     fseek(pFile, cur, 0);
					     fputc(k, pFile); cur++;
					     } while (k != EOF); 
					     fclose (pFile);
					}
					}
				}
				if (i == 2) 
				{
					if(buttons[i] == '0')
					{
					 pFile = fopen ("input.txt","a"); 
					 if (pFile!=NULL) 
					 { 
				    	 fprintf(pFile, "%d", n);
				    	 fclose (pFile); 
					 }
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

