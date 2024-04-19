/******************************************************************************************
Viet app ket hop file  + button
-Dem so lan nhan nut K1 va luu vao file text
-Nhan K2 de xem so lan nhan nut K1
-Nhan K3 de xoa so lan nhan ve 0
******************************************************************************************/


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

int buttons_fd,count=0;

void process_k1()
{
	FILE * pFile;
	count++;
	pFile = fopen ("text.txt", "w"); //mo file text.txt de ghi
	fprintf(pFile, "So lan nhan nut K1 la:%d",count);
	fclose(pFile);
	//return(0);
}

void process_k2()
{
	printf("So lan nhan nut K1 la:%d\n",count);
}

void process_k3()
{
	count=0;
	printf("Xoa so lan nhan nut K1 ve 0");

}


int main(void)
{

	char buttons[6] = {'0', '0', '0', '0', '0', '0'};
	char current_buttons[6];
	int count_of_changed_key;
	int i;
	//FILE * pFile;

	buttons_fd = open("/dev/buttons", 0);
	if (buttons_fd < 0) {
		perror("open device buttons");
		exit(1);
	}

	while (1) 
	
	{

		if (read(buttons_fd, current_buttons, sizeof current_buttons) != sizeof current_buttons) {
			perror("open device buttons error:");
			exit(1);
		}
		for (i = 0, count_of_changed_key = 0; i < sizeof buttons / sizeof buttons[0]; i++) {
			if (buttons[i] != current_buttons[i]) {
				buttons[i] = current_buttons[i];
				printf("key %d is %s",i+1, buttons[i] == '0' ? "up" : "down");
				//kiem tra
				if(current_buttons[0]=='1')
					process_k1();//k1 pressed
				else if (current_buttons[1]=='1')
					process_k2(); //k2 pressed
				else if (current_buttons[2]=='1')
					process_k3(); //k3 pressed
				count_of_changed_key++;
			}
		}
		if (count_of_changed_key) {
			printf("\n");
		}
	}
	close(buttons_fd);
	return 0;
}
