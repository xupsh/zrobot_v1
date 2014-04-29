#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>


char *addr[] = {"/sys/class/ultrasonic_class/ultrasonic/status",//status,set the work status
				//echo1
				"/sys/class/ultrasonic_class/ultrasonic/echo1",
				//echo2
				"/sys/class/ultrasonic_class/ultrasonic/echo2",
				//echo3
				"/sys/class/ultrasonic_class/ultrasonic/echo3",
				//mosi
				"/sys/class/ultrasonic_class/ultrasonic/mosi"
				};

//set whether the 3 echos  can work or not
char *work[] = {"0","16","32","48","64","80","96","112"};

char *data[] = {"17",//enable serial2paranell and send a trig 0x00000011
				"0",//disable
				};
int getdist()
{
	//TODO
	int echo1; 
	char buf[10];
	int value = 0;
	if((echo1 = open(addr[1],O_RDONLY)) == -1)
		err_sys("open error\n");
	memset(buf,0,sizeof(buf));
	read(echo1,buf,10);
	sscanf(buf,"%d",&value);
	close(echo1);
	return value;
}
