#include "xil_io.h"
#include "move.h"
#define AXI_GPIO_BASEADDR 0x41200000
#define AXI_PWM_BASEADDR  0x43C00000

void init_LED()
{
    fd = open(gpio_addr[0], MODE);
    if (fd < 0)
        printf("can't open gpio61 export\n");
    write(fd, "61", 2);
    close(fd);	

    fd = open(gpio_addr[0], MODE);
    if (fd < 0)
        printf("can't open gpio61 export\n");
    write(fd, "62", 2);
    close(fd);

    fd = open(gpio_addr[0], MODE);
    if (fd < 0)
        printf("can't open gpio61 export\n");
    write(fd, "63", 2);
    close(fd);

    fd = open(gpio_addr[0], MODE);
    if (fd < 0)
        printf("can't open gpio61 export\n");
    write(fd, "64", 2);
    close(fd);
}
/**
 * 小车向前运动控制函数
 * speed为前进速度
 * 使用axi gpio的4个gpio来控制轮子的方向
 * 设置4个pwm的占空比相同
 * */
void set_car_front(int speed)
{
	//set the for motor direction to be 0
	Xil_Out32(AXI_GPIO_BASEADDR, 0x00);
	//set the four motor's speed
	Xil_Out32(AXI_PWM_BASEADDR,      0x80000000 | speed);
	Xil_Out32(AXI_PWM_BASEADDR + 4,  0x80000000 | speed);
	Xil_Out32(AXI_PWM_BASEADDR + 8,  0x80000000 | speed);
	Xil_Out32(AXI_PWM_BASEADDR + 12, 0x80000000 | speed);
}
void set_car_back(int speed)
{
	//set the for motor direction to be 0
	Xil_Out32(AXI_GPIO_BASEADDR, 0xFF);
	//set the four motor's speed
	Xil_Out32(AXI_PWM_BASEADDR,      speed == 0 ? 0 : 0x80000000 | speed);
	Xil_Out32(AXI_PWM_BASEADDR + 4,  speed == 0 ? 0 : 0x80000000 | speed);
	Xil_Out32(AXI_PWM_BASEADDR + 8,  speed == 0 ? 0 : 0x80000000 | speed);
	Xil_Out32(AXI_PWM_BASEADDR + 12, speed == 0 ? 0 : 0x80000000 | speed);
}
/**
 * 设置小车向右转动
 * fast为左边轮子的速度，slow为右边轮子的速度
 * direction的低四位为四个轮子的方向
 * */
void set_car_right(int fast, int slow, int direction)
{
	int speed;
	Xil_Out32(AXI_GPIO_BASEADDR, direction);

	speed = fast;
	Xil_Out32(AXI_PWM_BASEADDR,      speed == 0 ? 0 : 0x80000000 | speed);
	Xil_Out32(AXI_PWM_BASEADDR + 4,  speed == 0 ? 0 : 0x80000000 | speed);

	speed = slow;
	Xil_Out32(AXI_PWM_BASEADDR + 8,  speed == 0 ? 0 : 0x80000000 | speed);
	Xil_Out32(AXI_PWM_BASEADDR + 12, speed == 0 ? 0 : 0x80000000 | speed);
}
void set_car_left(int fast, int slow, int direction)
{
	int speed;
	Xil_Out32(AXI_GPIO_BASEADDR, direction);

	speed = slow;
	Xil_Out32(AXI_PWM_BASEADDR,      speed == 0 ? 0 : 0x80000000 | speed);
	Xil_Out32(AXI_PWM_BASEADDR + 4,  speed == 0 ? 0 : 0x80000000 | speed);

	speed = fast;
	Xil_Out32(AXI_PWM_BASEADDR + 8,  speed == 0 ? 0 : 0x80000000 | speed);
	Xil_Out32(AXI_PWM_BASEADDR + 12, speed == 0 ? 0 : 0x80000000 | speed);
}
/**
 * 该函数为小车调用的总控制函数
 * angle参数为转动的角度，范围为[-90,90]
 * speed参数为转动的速度， 范围为[-90,90]
 * 该函数主要功能是对andle和speed进行解析， 并调用相应的操作函数对小车进行操作。
 * 如果你想改动小车的运动控制算法， 请参照该函数进行修改即可， 其他的部分不用修改
 * */
void smart_car_set(int angle, int speed)
{
	int fast = 0,slow = 0;
	if(angle == 0)
	{//如果角度为0
		syslog(LOG_DEBUG,"smart_car_set\n");
		if(speed >= 0) 
		{//如果speed >=0表示方向向前或者停止,这里的speed的值要加上5000是因为pwm的占空比的问题， 
		//于5000轮子基本转动不了
			speed = (speed == 0 ? 0 : (speed * 80 + 5000));
			set_car_front(speed);
		}
		else{
			speed = speed * -1 * 80 + 5000;
			set_car_back(speed);
		}
	}
	if(angle > 0 && angle <= 60)
	{//向右小角度度
		fast = speed > 0 ? (5000 + speed * 80) : ( 5000 + (-1) * speed * 80);
		slow = speed > 0 ? (5000 + speed * (80 - angle)) : ( 5000 + (-1) * speed * (80 - angle));
		if(speed > 0)//向右前进
			set_car_right(fast, slow, 0x00);
		else//向右后退
			set_car_right(fast, slow, 0xFF);
	}
	if(angle > 60 && angle <= 90)
	{//向右大角度
		fast = speed > 0 ? (5000 + speed * 80) : ( 5000 + (-1) * speed * 80);
		slow = speed > 0 ? (5000 + speed * (angle - 80)) : ( 5000 + (-1) * speed * (angle - 80));
		if(speed > 0)
			set_car_right(fast, slow, 0xCC);
		else
			set_car_right(fast, slow, 0x33);
	}
	if(angle >= -60 && angle < 0)
	{//向左小角度
		angle *= -1;
		fast = speed > 0 ? (5000 + speed * 80) : ( 5000 + (-1) * speed * 80);
		slow = speed > 0 ? (5000 + speed * (80 - angle)) : ( 5000 + (-1) * speed * (80 - angle));
		if(speed > 0)
			set_car_left(fast, slow, 0x00);
		else
			set_car_left(fast, slow, 0xFF);
	}
	if(angle >= -90 && angle < -60)
	{//向左大角度
		angle *= -1;
		fast = speed > 0 ? (5000 + speed * 80) : ( 5000 + (-1) * speed * 80);
		slow = speed > 0 ? (5000 + speed * (angle - 80)) : ( 5000 + (-1) * speed * (angle - 80));
		if(speed > 0)
			set_car_left(fast, slow, 0x33);
		else
			set_car_left(fast, slow, 0xCC);
	}
}
