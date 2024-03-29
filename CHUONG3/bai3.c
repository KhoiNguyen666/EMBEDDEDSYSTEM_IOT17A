#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

/**
 * @brief Điều khiển bật/tắt 4 leds
 *
 * @param fd led fd
 * @param state 0: tắt, 1: bật
 */
void set_all_leds(int fd, bool state)
{
    int i;
    for (i = 0; i < 4; i++)
    {
        ioctl(fd, state, i);
    }
}

/**
 * @brief Cho 4 led sáng theo giá trị nhị phân
 *
 * @param fd led fd
 * @param value giá trị nhị phân
 */
void set_leds_binary(int fd, int value)
{
    ioctl(fd, value & 0x01, 0);
    ioctl(fd, value & 0x02, 1);
    ioctl(fd, value & 0x04, 2);
    ioctl(fd, value & 0x08, 3);
}

/**
 * @brief 4 led sáng đuổi
 *
 * @param fd led fd
 * @param time thời gian thay đổi trạng thái
 */
void sang_duoi(int fd, long time)
{
    int i;
    int value = 0b1000;
    set_all_leds(fd, 0);
    usleep(time);
    for (i = 0; i < 4; i++)
    {
        set_leds_binary(fd, value >> i);
        usleep(time);
    }
}

/**
 * @brief 4 led sáng dần từ trên/dưới
 *
 * @param fd led fd
 * @param time thời gian thay đổi trạng thái
 * @param reverse 0: từ trên xuống, 1: từ dưới lên
 */
void sang_dan(int fd, long time, bool reverse)
{
    int i;
    int value;
    set_all_leds(fd, 0);
    usleep(time);

    if (reverse)
    {
        value = 0b0001;
        for (i = 0; i < 4; i++)
        {
            value = (value << i) | value;
            set_leds_binary(fd, value);
            usleep(time);
        }
    }
    else
    {
        value = 0b1000;
        for (i = 0; i < 4; i++)
        {
            value = (value >> i) | value;
            set_leds_binary(fd, value);
            usleep(time);
        }
    }
}

/**
 * @brief 4 led sáng nhị phân tăng/giảm dần
 *
 * @param fd led fd
 * @param time thời gian thay đổi trạng thái
 * @param reverse 0: tăng dần, 1: giảm dần
 */
void dem_nhi_phan(int fd, long time, bool reverse)
{
    int i;
    if (reverse)
    {
        for (i = 0b1111; i >= 0; i--)
        {
            set_leds_binary(fd, i);
            usleep(time);
        }
    }
    else
    {
        for (i = 0; i <= 0b1111; i++)
        {
            set_leds_binary(fd, i);
            usleep(time);
        }
    }
}

int main(int argc, char **argv)
{
    int buttons_fd, leds_fd;

    buttons_fd = open("/dev/buttons", 0);
    leds_fd = open("/dev/leds", 0);

    if (buttons_fd < 0 || leds_fd < 0)
    {
        perror("open device error");
        exit(1);
    }

    while (1)
    {
        char current_buttons[4];
        int i;

        if (read(buttons_fd, current_buttons, sizeof current_buttons) != sizeof current_buttons)
        {
            perror("read buttons:");
            exit(1);
        }

        if (current_buttons[0] == '1')
        {
            set_all_leds(leds_fd, 1);
            usleep(500000);
            set_all_leds(leds_fd, 0);
            usleep(500000);
            set_all_leds(leds_fd, 1);
            usleep(500000);
            set_all_leds(leds_fd, 0);
            usleep(500000);
        }
        else if (current_buttons[1] == '1')
        {
            sang_duoi(leds_fd, 500000);
            sang_duoi(leds_fd, 500000);
            sang_duoi(leds_fd, 500000);
        }
        else if (current_buttons[2] == '1')
        {
            dem_nhi_phan(leds_fd, 500000, 0);
        }
        else if (current_buttons[3] == '1')
        {
            sang_dan(leds_fd, 500000, 1);
        }
        else
        {
            set_all_leds(leds_fd, 0);
        }
    }
    close(buttons_fd);
    close(leds_fd);
    return 0;
}
