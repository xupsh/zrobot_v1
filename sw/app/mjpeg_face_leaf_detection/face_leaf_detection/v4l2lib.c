/****************************************************/
/*                                                  */
/*                      v4l2lib.c		                */
/*		             writen by heroxiao               */
/*                    	15/7/2013                   */
/*                                                  */
/****************************************************/

#include "v4l2lib.h"

#define  TRUE	1
#define  FALSE	0

int fd;
struct buffer *buffers;

int open_device()
{
	fd = open(FILE_VIDEO,O_RDWR);
	if(fd<0)
	{
		printf("Can not open V4l interface %s\n",FILE_VIDEO);
		exit(0);
	}

	return fd;
}

int close_device()
{	
	close(fd);
	return TRUE;
}

int init_device()
{
	v4l2_capability cap;
	v4l2_format fmt;
	v4l2_streamparm setfps;

	if(ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1)
    {
      printf("Error opening device %s: unable to query device.\n",FILE_VIDEO);
      return FALSE;
    }else
    	{
 	      printf("driver:\t\t%s\n",cap.driver);
        printf("card:\t\t%s\n",cap.card);
        printf("bus_info:\t%s\n",cap.bus_info);
        printf("version:\t%d\n",cap.version);
        printf("capabili ties:\t%x\n",cap.capabilities);

        if ((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == V4L2_CAP_VIDEO_CAPTURE)
        {
          printf("Device %s: supports capture.\n",FILE_VIDEO);
        }

	      if ((cap.capabilities & V4L2_CAP_STREAMING) == V4L2_CAP_STREAMING)
      	{
          printf("Device %s: supports streaming.\n",FILE_VIDEO);
        }
      }
    
    //set fmt
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
    fmt.fmt.pix.height = IMAGEHEIGHT;
    fmt.fmt.pix.width  = IMAGEWIDTH;
    fmt.fmt.pix.field  = V4L2_FIELD_INTERLACED;

    if(ioctl(fd, VIDIOC_S_FMT, &fmt) == -1)
    {
            printf("Unable to set format\n");
            return FALSE;
    }
    if(ioctl(fd, VIDIOC_G_FMT, &fmt) == -1)
    {
            printf("Unable to get format\n");
            return FALSE;
    }


    //set fps
    setfps.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    setfps.parm.capture.timeperframe.numerator = 1;
    setfps.parm.capture.timeperframe.denominator = 10;

    if(ioctl(fd, VIDIOC_S_PARM, &setfps) == -1)
    {
        printf("Unable to set frame rate\n");
        return FALSE;
    }
    else
    {
        printf("set fps OK!\n");
    }

    if(ioctl(fd, VIDIOC_G_PARM, &setfps) == -1)
    {
        printf("Unable to get frame rate\n");
        return FALSE;
    }
    else
    {
        printf("get fps OK!\n");
        printf("freq of frame:\t%d/%d\n",setfps.parm.capture.timeperframe.numerator,setfps.parm.capture.timeperframe.denominator);
    }

    //mmap
    if(init_mmap() == FALSE )
    {
        printf("cannot mmap!\n");
        return FALSE;
    }

    return TRUE;    
}

int init_mmap()
{
    v4l2_requestbuffers req;
    int n_buffers;

    req.count = num_buffer;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if(ioctl(fd, VIDIOC_REQBUFS, &req) == -1)
    {
        return FALSE;
    }

    if(req.count < 2)
    {
        return FALSE;
    }

    buffers = (struct buffer*)calloc(req.count, sizeof(*buffers));

    if(!buffers)
    {
        return FALSE;
    }

    for(n_buffers = 0; n_buffers < req.count; ++n_buffers)
    {
        v4l2_buffer buf;
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = n_buffers;

        if(ioctl(fd, VIDIOC_QUERYBUF, &buf) == -1)
        {
            return FALSE;
        }

        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start =
                mmap(NULL, // start anywhere// allocate RAM*4
                     buf.length,
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED,
                     fd, buf.m.offset);

        if(MAP_FAILED == buffers[n_buffers].start)
        {

            return FALSE;
        }
    }
    return TRUE;
}

int start_capturing()
{
    unsigned int i;
    for(i = 0; i < num_buffer; ++i)
    {
        v4l2_buffer buf;
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory =V4L2_MEMORY_MMAP;
        buf.index = i;
        if(-1 == ioctl(fd, VIDIOC_QBUF, &buf))
        {
            return FALSE;
        }
    }

    v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(-1 == ioctl(fd, VIDIOC_STREAMON, &type))
    {
        return FALSE;
    }
    return TRUE;
}

int stop_capturing()
{
    v4l2_buf_type type;
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(ioctl(fd, VIDIOC_STREAMOFF, &type) == -1)
    {
        return FALSE;
    }
    return TRUE;
}

int uninit_device()
{
    unsigned int i;

    for(i = 0; i < num_buffer; ++i)
    {
        if(-1 == munmap(buffers[i].start, buffers[i].length))
        {
            printf("munmap error\n");
            return FALSE;
        }

    }

    delete buffers;
    return TRUE;
}

int get_frame(unsigned char **yuv_buffer_pointer, int *len, int *index)
{
    v4l2_buffer queue_buf;

    queue_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    queue_buf.memory = V4L2_MEMORY_MMAP;

    if(ioctl(fd, VIDIOC_DQBUF, &queue_buf) == -1)
    {
        return FALSE;
    }

    *yuv_buffer_pointer = (unsigned char *)buffers[queue_buf.index].start;
    *len = buffers[queue_buf.index].length;
    *index = queue_buf.index;

    return TRUE;
}

int unget_frame(int index)
{
    if(index != -1)
    {
        v4l2_buffer queue_buf;
        queue_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        queue_buf.memory = V4L2_MEMORY_MMAP;
        queue_buf.index = index;

        if(ioctl(fd, VIDIOC_QBUF, &queue_buf) == -1)
        {
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}





