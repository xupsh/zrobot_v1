/*******************************************************************************
# Linux-UVC streaming input-plugin for MJPG-streamer                           #
#                                                                              #
# This package work with the Logitech UVC based webcams with the mjpeg feature #
#                                                                              #
# Copyright (C) 2005 2006 Laurent Pinchart &&  Michel Xhaard                   #
#                    2007 Lucas van Staden                                     #
#                    2007 Tom Stöveken                                         #
#                                                                              #
# This program is free software; you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation; either version 2 of the License, or            #
# (at your option) any later version.                                          #
#                                                                              #
# This program is distributed in the hope that it will be useful,              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of               #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                #
# GNU General Public License for more details.                                 #
#                                                                              #
# You should have received a copy of the GNU General Public License            #
# along with this program; if not, write to the Free Software                  #
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA    #
#                                                                              #
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include <pthread.h>
#include <syslog.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>

#include "../../utils.h"
//#include "../../mjpg_streamer.h"
#include "v4l2uvc.h" // this header will includes the ../../mjpg_streamer.h
#include "huffman.h"
#include "jpeg_utils.h"
#include "dynctrl.h"
//#include "uvcvideo.h"

#define INPUT_PLUGIN_NAME "UVC webcam grabber"
#define buffer_n 2
#define W_LOCK  0
#define R_LOCK  1

/*
 * UVC resolutions mentioned at: (at least for some webcams)
 * http://www.quickcamteam.net/hcl/frame-format-matrix/
 */
static const struct {
    const char *string;
    const int width, height;
} resolutions[] = {
    { "QSIF", 160,  120  },
    { "QCIF", 176,  144  },
    { "CGA",  320,  200  },
    { "QVGA", 320,  240  },
    { "CIF",  352,  288  },
    { "VGA",  640,  480  },
    { "SVGA", 800,  600  },
    { "XGA",  1024, 768  },
    { "SXGA", 1280, 1024 }
};

/* private functions and variables to this plugin */
static globals *pglobal;
static int gquality = 80;
static unsigned int minimum_size = 0;
static int dynctrls = 1;
static int ID;
static pthread_t threadID;

void *cam_thread(void *);
void cam_cleanup(void *);
void help(void);
int input_cmd(int plugin, unsigned int control, unsigned int group, int value);

struct rgb_buffer
{
  unsigned char *buf;
  int  semid,shmid;
}buffer[buffer_n];

union semun 
{ 
    int val; 
    struct semid_ds *buf; 
    unsigned short int *array; 
    struct seminfo *__buf; 
}; 

int getsem(int semid,int num)
{
  struct sembuf sem_buf={num,-1,IPC_NOWAIT|SEM_UNDO};
  return semop(semid,&sem_buf,1);   
}

int freesem(int semid,int num)
{
  struct sembuf sem_buf={num,1,IPC_NOWAIT|SEM_UNDO};
  return semop(semid,&sem_buf,1);
}

/*** plugin interface functions ***/
/******************************************************************************
Description.: This function ializes the plugin. It parses the commandline-
              parameter and stores the default and parsed values in the
              appropriate variables.
Input Value.: param contains among others the command-line string
Return Value: 0 if everything is fine
              1 if "--help" was triggered, in this case the calling programm
              should stop running and leave.
******************************************************************************/
int input_init(input_parameter *param, int id)
{
    char *dev = "/dev/video0", *s;
    int width = 640, height = 480, fps = 5, format = V4L2_PIX_FMT_MJPEG, i;
    /* initialize the mutes variable */
    if(pthread_mutex_init(&cams[id].controls_mutex, NULL) != 0) {
        IPRINT("could not initialize mutex variable\n");
        exit(EXIT_FAILURE);
    }

    param->argv[0] = INPUT_PLUGIN_NAME;

    /* show all parameters for DBG purposes */
    for(i = 0; i < param->argc; i++) {
        DBG("argv[%d]=%s\n", i, param->argv[i]);
    }

    /* parse the parameters */
    reset_getopt();
    while(1) {
        int option_index = 0, c = 0;
        static struct option long_options[] = {
            {"h", no_argument, 0, 0},
            {"help", no_argument, 0, 0},
            {"d", required_argument, 0, 0},
            {"device", required_argument, 0, 0},
            {"r", required_argument, 0, 0},
            {"resolution", required_argument, 0, 0},
            {"f", required_argument, 0, 0},
            {"fps", required_argument, 0, 0},
            {"y", no_argument, 0, 0},
            {"yuv", no_argument, 0, 0},
            {"q", required_argument, 0, 0},
            {"quality", required_argument, 0, 0},
            {"m", required_argument, 0, 0},
            {"minimum_size", required_argument, 0, 0},
            {"n", no_argument, 0, 0},
            {"no_dynctrl", no_argument, 0, 0},
            {"l", required_argument, 0, 0},
            {"led", required_argument, 0, 0},
            {0, 0, 0, 0}
        };

        /* parsing all parameters according to the list above is sufficent */
        c = getopt_long_only(param->argc, param->argv, "", long_options, &option_index);

        /* no more options to parse */
        if(c == -1) break;

        /* unrecognized option */
        if(c == '?') {
            help();
            return 1;
        }

        /* dispatch the given options */
        switch(option_index) {
            /* h, help */
        case 0:
        case 1:
            DBG("case 0,1\n");
            help();
            return 1;
            break;

            /* d, device */
        case 2:
        case 3:
            DBG("case 2,3\n");
            dev = strdup(optarg);
            break;

            /* r, resolution */
        case 4:
        case 5:
            DBG("case 4,5\n");
            width = -1;
            height = -1;

            /* try to find the resolution in lookup table "resolutions" */
            for(i = 0; i < LENGTH_OF(resolutions); i++) {
                if(strcmp(resolutions[i].string, optarg) == 0) {
                    width  = resolutions[i].width;
                    height = resolutions[i].height;
                }
            }
            /* done if width and height were set */
            if(width != -1 && height != -1)
                break;
            /* parse value as decimal value */
            width  = strtol(optarg, &s, 10);
            height = strtol(s + 1, NULL, 10);
            break;

            /* f, fps */
        case 6:
        case 7:
            DBG("case 6,7\n");
            fps = atoi(optarg);
            break;

            /* y, yuv */
        case 8:
        case 9:
            DBG("case 8,9\n");
            format = V4L2_PIX_FMT_YUYV;
            break;

            /* q, quality */
        case 10:
        case 11:
            DBG("case 10,11\n");
            format = V4L2_PIX_FMT_YUYV;
            gquality = MIN(MAX(atoi(optarg), 0), 100);
            break;

            /* m, minimum_size */
        case 12:
        case 13:
            DBG("case 12,13\n");
            minimum_size = MAX(atoi(optarg), 0);
            break;

            /* n, no_dynctrl */
        case 14:
        case 15:
            DBG("case 14,15\n");
            dynctrls = 0;
            break;

            /* l, led */
        case 16:
        case 17:/*
        DBG("case 16,17\n");
        if ( strcmp("on", optarg) == 0 ) {
          led = IN_CMD_LED_ON;
        } else if ( strcmp("off", optarg) == 0 ) {
          led = IN_CMD_LED_OFF;
        } else if ( strcmp("auto", optarg) == 0 ) {
          led = IN_CMD_LED_AUTO;
        } else if ( strcmp("blink", optarg) == 0 ) {
          led = IN_CMD_LED_BLINK;
        }*/
            break;

        default:
            DBG("default case\n");
            help();
            return 1;
        }
    }
    DBG("input id: %d\n", id);
    pglobal=param->global;
    ID=id;
   
    /* display the parsed values */
    IPRINT("Using V4L2 device.: %s\n", dev);
    IPRINT("Desired Resolution: %i x %i\n", width, height);
    IPRINT("Frames Per Second.: %i\n", fps);
    IPRINT("Format............: %s\n", (format == V4L2_PIX_FMT_YUYV) ? "YUV" : "MJPEG");
    if(format == V4L2_PIX_FMT_YUYV)
        IPRINT("JPEG Quality......: %d\n", gquality);
  
  key_t key_buffer[buffer_n],key_sem[buffer_n];     
  //获取键值
  for(i=0;i<buffer_n;i++)
  {
    char tmp[30];
    int j;
    j=sprintf(tmp,"/tmp/buffer%d",i);
    tmp[j]='\0';
    key_buffer[i]=ftok(tmp,i+1);
    j=sprintf(tmp,"/tmp/sem%d",i);
    tmp[j]='\0';
    key_sem[i]=ftok(tmp,i+1);
  }
  
  //获取并映射共享内存
  for(i=0;i<buffer_n;i++)
  {
    buffer[i].shmid=shmget(key_buffer[i],IMAGEWIDTH*IMAGEHEIGHT*3,IPC_CREAT|0666);
    if(buffer[i].shmid<0)
		{
			printf("get share memory wrong!\n");
			exit(0);
		}
		buffer[i].buf =(unsigned char *)shmat(buffer[i].shmid,0,0);
		if(buffer[i].buf==NULL)
		{
			printf("map share memory wrong!\n");
			exit(0);
		}
  }
  
	//获取信号量并赋初值
	for(i=0;i<buffer_n;i++)
	{
	  buffer[i].semid=semget(key_sem[i],2,IPC_CREAT|0666|IPC_NOWAIT);
	  if(buffer[i].semid<0)
	  {
	    printf("get sem wrong!\n");
			exit(0);
	  }  
	  
	  union semun sem_union;
    sem_union.val=0;
    if (semctl(buffer[i].semid,W_LOCK,SETVAL,sem_union)==-1) 
    {
       printf("Sem init wrong!\n");
       exit(1);
    }
    if (semctl(buffer[i].semid,R_LOCK,SETVAL,sem_union)==-1) 
    {
       printf("Sem init wrong!\n");
       exit(1);
    }    
	}
	
  pid_t pid;
  pid=fork();
  if(pid<0)
  {
    printf("Can not creat son process!\n");
    exit(0);
  }      
  if(pid==0)
  {
    execl("/usr/bin/taskset","taskset","2","./facedetection",(char *)0);
  }
  return 0;
}

/******************************************************************************
Description.: Stops the execution of worker thread
Input Value.: -
Return Value: always 0
******************************************************************************/
int input_stop(int id)
{
    DBG("will cancel camera thread #%02d\n", id);
    pthread_cancel(threadID);
    return 0;
}

/******************************************************************************
Description.: spins of a worker thread
Input Value.: -
Return Value: always 0
******************************************************************************/
int input_run(int id)
{
    pglobal->in[ID].buf=malloc(IMAGEWIDTH*IMAGEHEIGHT<<1);
    if(pglobal->in[ID].buf==NULL)
    {
      printf("could not allocate globle memory buf!\n");
      exit(1);
    }
    
    DBG("launching camera thread #%02d\n", id);
    /* create thread and pass context to thread function */
    pthread_create(&(threadID), NULL, cam_thread, NULL);
    pthread_detach(threadID);
    int i;
    for(i=0;i<buffer_n;i++)
    {
      //释放读锁
      freesem(buffer[i].semid,R_LOCK);
    }
    return 0;
}

/*** private functions for this plugin below ***/
/******************************************************************************
Description.: print a help message to stderr
Input Value.: -
Return Value: -
******************************************************************************/
void help(void)
{
    int i;

    fprintf(stderr, " ---------------------------------------------------------------\n" \
    " Help for input plugin..: "INPUT_PLUGIN_NAME"\n" \
    " ---------------------------------------------------------------\n" \
    " The following parameters can be passed to this plugin:\n\n" \
    " [-d | --device ].......: video device to open (your camera)\n" \
    " [-r | --resolution ]...: the resolution of the video device,\n" \
    "                          can be one of the following strings:\n" \
    "                          ");

    for(i = 0; i < LENGTH_OF(resolutions); i++) {
        fprintf(stderr, "%s ", resolutions[i].string);
        if((i + 1) % 6 == 0)
            fprintf(stderr, "\n                          ");
    }
    fprintf(stderr, "\n                          or a custom value like the following" \
    "\n                          example: 640x480\n");

    fprintf(stderr, " [-f | --fps ]..........: frames per second\n" \
    " [-y | --yuv ]..........: enable YUYV format and disable MJPEG mode\n" \
    " [-q | --quality ]......: JPEG compression quality in percent \n" \
    "                          (activates YUYV format, disables MJPEG)\n" \
    " [-m | --minimum_size ].: drop frames smaller then this limit, useful\n" \
    "                          if the webcam produces small-sized garbage frames\n" \
    "                          may happen under low light conditions\n" \
    " [-n | --no_dynctrl ]...: do not initalize dynctrls of Linux-UVC driver\n" \
    " [-l | --led ]..........: switch the LED \"on\", \"off\", let it \"blink\" or leave\n" \
    "                          it up to the driver using the value \"auto\"\n" \
    " ---------------------------------------------------------------\n\n");
}

/******************************************************************************
Description.: this thread worker grabs a frame and copies it to the global buffer
Input Value.: unused
Return Value: unused, always NULL
******************************************************************************/
void *cam_thread(void *arg)
{    
    int i;
    int flag;
    /* set cleanup handler to cleanup allocated ressources */
    pthread_cleanup_push(cam_cleanup, NULL);
    while(!pglobal->stop) {
      flag=0;
      for(i=0;i<buffer_n;i++)
      {
        //获取写锁
        if(getsem(buffer[i].semid,W_LOCK)==0)
        {          
           /* copy JPG picture to global buffer */
          pthread_mutex_lock(&pglobal->in[ID].db);

        /*
         * If capturing in YUV mode convert to JPEG now.
         * This compression requires many CPU cycles, so try to avoid YUV format.
         * Getting JPEGs straight from the webcam, is one of the major advantages of
         * Linux-UVC compatible devices.
         */         
          pglobal->in[ID].size = compress_bmp_to_jpeg(buffer[i].buf, pglobal->in[ID].buf, IMAGEWIDTH*IMAGEHEIGHT<<1, gquality);
          /* signal fresh_frame */
          pthread_cond_broadcast(&pglobal->in[ID].db_update);
          pthread_mutex_unlock(&pglobal->in[ID].db);
          //释放读锁
          while(freesem(buffer[i].semid,R_LOCK)<0);
          flag=1;
        }        
     }
     if(flag==0)
     {        
        usleep(300);
     }
   }

    DBG("leaving input thread, calling cleanup function now\n");
    pthread_cleanup_pop(1);

    return NULL;
}

/******************************************************************************
Description.:
Input Value.:
Return Value:
******************************************************************************/
void cam_cleanup(void *arg)
{
    static unsigned char first_run = 1;
    
    if(!first_run) {
        DBG("already cleaned up ressources\n");
        return;
    }

    first_run = 0;
    IPRINT("cleaning up ressources allocated by input thread\n");
   
    if(pglobal->in[ID].buf != NULL)
        free(pglobal->in[ID].buf);
}

/******************************************************************************
Description.: process commands, allows to set v4l2 controls
Input Value.: * control specifies the selected v4l2 control's id
                see struct v4l2_queryctr in the videodev2.h
              * value is used for control that make use of a parameter.
Return Value: depends in the command, for most cases 0 means no errors and
              -1 signals an error. This is just rule of thumb, not more!
******************************************************************************/
int input_cmd(int plugin_number, unsigned int control_id, unsigned int group, int value)
{
    int ret = -1;    
    return ret;
}

