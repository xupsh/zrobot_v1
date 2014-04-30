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

#define MODE (O_WRONLY | O_TRUNC)


static char *gpio_addr[] = {
	"/sys/class/gpio/export",
	"/sys/class/gpio/gpio61/direction/","/sys/class/gpio/gpio61/value/",
	"/sys/class/gpio/gpio62/direction/","/sys/class/gpio/gpio62/value/",
	"/sys/class/gpio/gpio63/direction/","/sys/class/gpio/gpio63/value/",
	"/sys/class/gpio/gpio64/direction/","/sys/class/gpio/gpio64/value/"
};

extern void init_LED();
extern void set_car_front(int speed);
extern void set_car_back(int speed);
extern void set_car_right(int fast, int slow, int direction);
extern void set_car_left(int fast,  int slow, int direction);
extern void smart_car_set(int angle, int speed);

#endif
