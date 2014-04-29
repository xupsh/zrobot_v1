#include "smart_car_move.h"

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
void set_clockwise()
{
	char *ss = "7000";
	int i;
	if((fd = open(pwm_addr[0],MODE)) == -1)
		err_sys("can't open value\n");
	write(fd, "CC",2);
	close(fd);
	for(i = 1; i <= 4; i++)
	{
		if((fd = open(pwm_addr[i],MODE)) == -1)
			err_sys("can not open %s",pwm_addr[i]);
		write(fd, ss, 4);
		close(fd);
	}
}

void set_direction(char *value)
{
	printf("++test value = %s\n",value);
	if((fd = open(pwm_addr[0],MODE)) == -1)
		err_sys("can not open %s\n",pwm_addr[0]);
	write(fd, value, 2);
	close(fd);
}
void set_car_go(int pwmnum, char *speed)
{
	printf("++test pwmnum=%d,speed = %s\n",pwmnum,speed);
	if((fd = open(pwm_addr[pwmnum],MODE)) == -1)
		err_sys("can not open %s\n",pwm_addr[pwmnum]);
	write(fd,speed,strlen(speed));
	close(fd);	
}
void set_car_front(char *speed)
{
	printf("++test front speed =%s \n",speed);
	int i ;
	set_direction("00");
	for(i = 1; i <= 4 ; i++)
		set_car_go(i,speed);
}
void set_car_back(char *speed)
{
	printf("++test back speed = %d\n",speed);
	int i;
	set_direction("FF");
	for(i = 1 ; i <= 4 ; i++)
		set_car_go(i,speed);
}
void set_car_right(int fast, int slow, char *value)
{
		printf("++test right slow= %d,fast=%d,value=%s\n",slow,fast,value);
		set_direction(value);
		CONVERT(fast);
		set_car_go(1,cspeed);
		set_car_go(2,cspeed);
		CONVERT(slow);
		set_car_go(3,cspeed);
		set_car_go(4,cspeed);
}
void set_car_left(int fast, int slow, char *value)
{
		printf("++test left slow= %d,fast=%d,value=%s",slow,fast,value);
		set_direction(value);
		CONVERT(fast);
		set_car_go(3,cspeed);
		set_car_go(4,cspeed);
		CONVERT(slow);
		set_car_go(1,cspeed);
		set_car_go(2,cspeed);
}
void smart_car_set(int angle, int speed)
{
	printf("++test set angle=%d,speed=%d\n",angle,speed);
	syslog(LOG_DEBUG,"smart_car_set\n");
	int fast = 0,slow = 0;
	if(angle == 0)
	{
		syslog(LOG_DEBUG,"smart_car_set\n");
		if(speed >= 0) 
		{
			speed = (speed == 0 ? 0 : (speed * 80 + 5000));
			CONVERT(speed);
			set_car_front(cspeed);
		}
		else{
			speed = speed * -1 * 80 + 5000;
			CONVERT(speed);
			set_car_back(cspeed);
		}
	}
	if(angle > 0 && angle <= 60)
	{
		fast = speed > 0 ? (5000 + speed * 80) : ( 5000 + (-1) * speed * 80);
		slow = speed > 0 ? (5000 + speed * (80 - angle)) : ( 5000 + (-1) * speed * (80 - angle));
		if(speed > 0)
			set_car_right(fast, slow, "00");
		else
			set_car_right(fast, slow, "FF");
	}
	if(angle > 60 && angle <= 90)
	{
		fast = speed > 0 ? (5000 + speed * 80) : ( 5000 + (-1) * speed * 80);
		slow = speed > 0 ? (5000 + speed * (angle - 80)) : ( 5000 + (-1) * speed * (angle - 80));
		if(speed > 0)
			set_car_right(fast, slow, "CC");
		else
			set_car_right(fast, slow, "33");
	}
	if(angle >= -60 && angle < 0)
	{
		angle *= -1;
		fast = speed > 0 ? (5000 + speed * 80) : ( 5000 + (-1) * speed * 80);
		slow = speed > 0 ? (5000 + speed * (80 - angle)) : ( 5000 + (-1) * speed * (80 - angle));
		if(speed > 0)
			set_car_left(fast, slow, "00");
		else
			set_car_left(fast, slow, "FF");
	}
	if(angle >= -90 && angle < -60)
	{
		angle *= -1;
		fast = speed > 0 ? (5000 + speed * 80) : ( 5000 + (-1) * speed * 80);
		slow = speed > 0 ? (5000 + speed * (angle - 80)) : ( 5000 + (-1) * speed * (angle - 80));
		if(speed > 0)
			set_car_left(fast, slow, "33");
		else
			set_car_left(fast, slow, "CC");
	}
}
