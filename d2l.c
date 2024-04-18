// 1. Viết chương trình khí 10 ký tự "b' vào file có tên là test. xt (1 điểm)
// 2. Nhấn/nhà K2 để xem file test.xt (1 điểm)
// 3. Nhấm nhà k3 thêm vào cuối file ("lo me ban " vào cuố file tert x. (1 đêm)
// 4. Nhập n: (từ 1 → 5)
// Nhấn/nhà K4 chương trình sẽ phát ra n tiếng ở tần số 1000 Hz (thời gian delay giữa 2 lần phát là 500 ms), đồng thời hiền thị giá trị n dưới dạng nhị phân trên 4 led. (3 điểm)
// (mặc định ban dầu 4 led tắt)

#include <pthread.h>
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
#define PWM_IOCTL_SET_FREQ 1
#define PWM_IOCTL_STOP 0
int fd_led, fd_button, fd_pwm;
int i, n;

void buzzer(int n)
{
    for (i = 0; i < n; i++)
    {
        printf("Buzzer ON\n");
        usleep(500000);
        printf("Buzzer OFF\n");
        usleep(500000);
    }
}

void print_binary(int value)
{
    printf("%d%d%d%d\n", (value & 0x08) >> 3, (value & 0x04) >> 2, (value & 0x02) >> 1,(value & 0x01));
}

int main(int argc, char **argv)
{
    FILE *fpFile;
    char buttons[6] = {'0', '0', '0', '0', '0', '0'};
    char key = 0xff;
    // Viết chương trình khí 10 ký tự "b' vào file có tên là test. xt
    fpFile = fopen("test.xt", "w");
    fprintf(fpFile, "bbbbbbbbbb");
    fclose(fpFile);

    // Tắt All Led
    printf("Led 0 OFf\n");
    printf("Led 1 OFf\n");
    printf("Led 2 OFf\n");
    printf("Led 3 OFf\n");
    
    while (1)
    {
    key = getchar();

        switch (key)
        {
        // Nhấn nút K2
        case '1':
            fpFile = fopen("test.xt", "r+");
            char c;
            while ((c = fgetc(fpFile)) != EOF)
            {
                printf("%c", c);
            }
            fclose(fpFile);

            break;
        // Nhấn nút K3
        case '2':
            fpFile = fopen("test.xt", "a");
            fprintf(fpFile, "lo me ban ");
            fclose(fpFile);
            break;
        // Nhấn nút K4
        case '3':
            printf("Nhap n: ");
            scanf("%d", &n);
            print_binary(n);
            buzzer(n);
            break;
        }
    }

    return 0;
}
