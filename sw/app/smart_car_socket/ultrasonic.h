/*
 * Copyright (c) 2013~2014
 *
 * This source code is released for free distribution under the terms of the
 * GNU General Public License
 *
 * Author:       zlpan
 * Created Time: Wed Jul 31 17:41:57 2013
 * File Name:    ultrasonic.h
 *
 * Description:  
 */

#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#define ULTRASONIC_IOC_MAGIC    'Z' 

#define ULTRASONIC_STATUS_WRITE _IOW(ULTRASONIC_IOC_MAGIC, 1, int)
#define ULTRASONIC_STATUS_READ  _IOR(ULTRASONIC_IOC_MAGIC, 2, int)
#define ULTRASONIC_ECHO1_READ   _IOR(ULTRASONIC_IOC_MAGIC, 3, int)
#define ULTRASONIC_ECHO2_READ   _IOR(ULTRASONIC_IOC_MAGIC, 4, int)
#define ULTRASONIC_ECHO3_READ   _IOR(ULTRASONIC_IOC_MAGIC, 5, int)
#define ULTRASONIC_MOSI_READ    _IOR(ULTRASONIC_IOC_MAGIC, 6, int)
#define ULTRASONIC_MOSI_WRITE   _IOW(ULTRASONIC_IOC_MAGIC, 7, int)


#define ULTRASONIC_IOC_MAXNR     10

static int enable = 0x30;
static int send_trig = 0x11;
static int s2p = 0x10;
static int fd = 0;
extern int getDist();
extern int ultrasonic_init();
extern void ultrasonic_close();
#endif
