###############################################################
#
# Purpose: Makefile for "M-JPEG Streamer"
# Author.: Tom Stoeveken (TST)
# Version: 0.3
# License: GPL
#
###############################################################

CC = arm-xilinx-linux-gnueabi-gcc
CPP = arm-xilinx-linux-gnueabi-g++

CFLAGS += -O1 -DLINUX -D_GNU_SOURCE -Wall -shared -fPIC -I/opt/mjpg/jepg/install/include
#CFLAGS += `pkg-config --cflags opencv`

#CFLAGS += -g
#CFLAGS += -DDEBUG

ifeq ($(USE_LIBV4L2),true)
LFLAGS += -lv4l2
CFLAGS += -DUSE_LIBV4L2
endif


LFLAGS += -L/opt/mjpg/jepg/install/lib -ljpeg
#LFLAGS += -L/opt/facedetection/lib -lfacedetection
#LFLAGS += `pkg-config --libs opencv`

all: input_uvc_opencv.so

clean:
	rm -f *.a *.o core *~ *.so *.lo

input_uvc_opencv.so: $(OTHER_HEADERS) input_uvc_opencv.c v4l2uvc.lo jpeg_utils.lo dynctrl.lo 
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ input_uvc_opencv.c v4l2uvc.lo jpeg_utils.lo dynctrl.lo

v4l2uvc.lo: huffman.h uvc_compat.h v4l2uvc.c v4l2uvc.h
	$(CC) -c $(CFLAGS) -o $@ v4l2uvc.c

jpeg_utils.lo: jpeg_utils.c jpeg_utils.h
	$(CC) -c $(CFLAGS) -o $@ jpeg_utils.c

dynctrl.lo: dynctrl.c dynctrl.h
	$(CC) -c $(CFLAGS) -o $@ dynctrl.c
#facedetection.o:facedetection.c facedetection.h
#	$(CPP) -O2 -o $@ facedetection.c `pkg-config --cflags --libs opencv`
