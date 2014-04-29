/*
 * Copyright (c) 2013~2014
 *
 * This source code is released for free distribution under the terms of the
 * GNU General Public License
 *
 * Author:       zlpan
 * Created Time: Wed Jul 31 17:44:18 2013
 * File Name:    ultrasonic.c
 *
 * Description:  
 */

#include "ultrasonic.h"

int getDist()
{
	int dist = 0;
    int reg0 = 0;
    ioctl(fd, ULTRASONIC_STATUS_WRITE, &send_trig);
	while(!(reg0 & 0x00000002))
		ioctl(fd, ULTRASONIC_STATUS_READ, &reg0);
	 reg0 = reg0 & 0xFFFFFFFD;
	 ioctl(fd, ULTRASONIC_STATUS_WRITE, &reg0);
	 ioctl(fd, ULTRASONIC_ECHO1_READ, &dist);
	 printf("dist = %d\n", dist & 0x000003ff);
	 return dist & 0x000003ff;
}
int ultrasonic_init()
{
	if((fd = open("/dev/ultrasonic", O_RDWR)) == -1)
	{
		printf("open error\n");
		return -1;
	}
	int ret = ioctl(fd, ULTRASONIC_MOSI_WRITE, &enable);
	if(ret == -1)
		return -1;
	ret = ioctl(fd, ULTRASONIC_STATUS_WRITE, &s2p);
	if(ret == -1)
		return -1;
	return 0;
}
void ultrasonic_close()
{
	close(fd);
}
