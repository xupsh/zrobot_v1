#ifndef SMARTCARMOVE_H
#define SMARTCARMOVE_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <memory.h>
#include "move.h"

static int fd;
static char cspeed[6] = {0};

#define MODE (O_WRONLY | O_TRUNC)
#define CONVERT(speed)    {memset(cspeed,0,6);\
						   snprintf(cspeed,6,"%d",speed);}


static char *pwm_addr[] = {
	"/sys/class/pwm_class/pwm_device/value", //set the direction and led
	"/sys/class/pwm_class/pwm_device/pwm1_speed",
	"/sys/class/pwm_class/pwm_device/pwm2_speed",
	"/sys/class/pwm_class/pwm_device/pwm3_speed",
	"/sys/class/pwm_class/pwm_device/pwm4_speed"
};
static char *gpio_addr[] = {
	"/sys/class/gpio/export",
	"/sys/class/gpio/gpio61/direction/","/sys/class/gpio/gpio61/value/",
	"/sys/class/gpio/gpio62/direction/","/sys/class/gpio/gpio62/value/",
	"/sys/class/gpio/gpio63/direction/","/sys/class/gpio/gpio63/value/",
	"/sys/class/gpio/gpio64/direction/","/sys/class/gpio/gpio64/value/"
};

extern void init_LED();
extern void set_direction();
extern void set_car_go(int pwmnum, char *speed);
extern void set_car_front(char *speed);
extern void set_car_back(char *speed);
extern void set_car_right(int fast, int slow, char *value);
extern void set_car_left(int fast,  int slow, char *value);
extern void smart_car_set(int angle, int speed);

#endif
