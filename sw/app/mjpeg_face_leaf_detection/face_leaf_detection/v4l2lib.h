/****************************************************/
/*                                                  */
/*                      v4l2lib.h		    */
/*		   writen by heroxiao               */
/*                 	15/7/2013                   */
/*                                                  */
/****************************************************/

#ifndef __V4LGRAB_H__
#define __V4LGRAB_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <asm/types.h>
#include <linux/videodev2.h>

#define num_buffer 2
#define FILE_VIDEO "/dev/video0"
#define  IMAGEWIDTH    640
#define  IMAGEHEIGHT   480

struct buffer
    {
        void * start;
        size_t length;
    };

int open_device();
int close_device();
int init_device();
int init_mmap();
int start_capturing();
int stop_capturing();
int uninit_device();
int get_frame(unsigned char **yuv_buffer_pointer, int *len, int *index);
int unget_frame(int index);

#endif
