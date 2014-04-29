#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stddef.h>        /* for offsetof */
#include <string.h>        /* for convenience */
#include <unistd.h>        /* for convenience */
#include <errno.h>
#include <syslog.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/resource.h>

#include<netinet/in.h>//struct sockaddr_in
#include <pthread.h> //pthread support

#define BUFLEN	128
#define QLEN 1024

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

#include "ctrlcmds.h"
#include "ctrlprefix.h"
#include "zynq_server.h"
int		clfd;
pthread_t tid;
int speed_up_mode_flag = 1;
//get speed thread progress
void *getSpeed(void *arg)
{
	int speed = 0;
	int ret;
	unsigned char buff[4];
	while(speed_up_mode_flag == 1)
	{
		printf("speed = %d\n",speed);
		if(speed == 999999) speed = 0;
		sprintf(buff, "%d", speed);
		ret = send(clfd, buff, sizeof(buff), 0);
		if(ret == -1)
		{
			printf("send error");
			close(clfd);
			break;
		}
		sleep(1);
		speed++;
	}
	pthread_exit(NULL);
}
int hrobot_tcp_receive(TCP_CTRL_FRAME *frame, uint8_t *buf)
{
	int n,i, err, fd;
	while(1){
		memset(frame,0,sizeof(TCP_CTRL_FRAME));
		memset(buf,0,HROBOT_TCP_MAX_DATA_LENGTH);

		if ((n = recv(clfd,frame, HROBOT_TCP_CTRL_FRAME_SIZE, 0)) > 0)
		{
			frame->cmd = ntohs(frame->cmd);
			frame->length = ntohs(frame->length);
			printf("frame_CTR:recv %d data",n);
			printf("cmd:%d, length:%d",frame->cmd, frame->length);
		}
		switch(frame->cmd)
		{
		case SPEED_UP:
			//add you code here
			//create a thread to get the speed of pwm
			speed_up_mode_flag = 1;
			err = pthread_create(&tid, NULL, getSpeed, (void *)0);
			if(err != 0)
			{
				err_sys("cannot create thread");
			}
			break;
		case SPEED_DOWN:
			//close getspeed thread
			speed_up_mode_flag = 0;
			break;
		case ENTER_AUTO_CONTROL_MODE:
			//add you code here
			//you'd better create a thread
			break;
		case ENTER_REAL_CONTROL_MODE:
			//add your code here
			//just stop the auto mode thread
			break;
		case OPERATE_CAR_LEFT:
		case OPERATE_CAR_RIGHT:
			if ((n = recv(clfd, buf, frame->length, 0)) > 0)
			{
				//the speed and angel is in the buf
				//you can add your control algorithm below
			}
			break;
		default:
			break;
		}
	}
	return 0;
}

int tcp_listen(const char *serv, socklen_t *addrlenp)
{
	struct addrinfo	*res, *ressave;
	struct addrinfo	hint;
	int             on = 1;
	int             listenfd;
	int 			err;
	int             n;
	char            *host;

#ifdef _SC_HOST_NAME_MAX
	n = sysconf(_SC_HOST_NAME_MAX);
	if(n < 0)
#endif
		n = HOST_NAME_MAX;
	host = (char *)malloc(n);
	if(!host)
	{
		err_sys("mallo error");
	}
	if(gethostname(host, n) < 0)
		err_sys("get hostname error");
	memset(&hint, 0, sizeof(struct addrinfo));

	hint.ai_flags = AI_PASSIVE;
	hint.ai_family = AF_UNSPEC;
	hint.ai_socktype = SOCK_STREAM;

	if ((err = getaddrinfo(host, serv, &hint, &res)) != 0) {
		err_quit("tcp_listen error for %s %s %s",host, serv, gai_strerror(err));
	}
	ressave = res;
	do{
		listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if(listenfd < 0)
			continue;
		setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on,sizeof(on));
		if(bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
			break;
		close(listenfd);
	}while((res = res->ai_next) != NULL);

	if(res == NULL)
		err_sys("tcp listen error for %s, %s",host, serv);
	listen(listenfd, QLEN);
	if(addrlenp){
		*addrlenp = res->ai_addrlen;
	}
	freeaddrinfo(ressave);
	return listenfd;
}

int main(int argc, char *argv[])
{
	struct sockaddr_storage  cliaddr;
	socklen_t                len, addrlen;
	int                      listenfd, connfd;
	TCP_CTRL_FRAME           ctrl_frame;
	uint8_t                  data[HROBOT_TCP_MAX_DATA_LENGTH];
	if(argc != 2)
		err_quit("usage: zynq_serve_arm  <service or port>");
	listenfd = tcp_listen(argv[1], &addrlen);
	for ( ; ; ) {
		len = sizeof(struct sockaddr_in);
		printf("accept\n");
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
		if (clfd < 0) {
			err_quit("Zynq@Server: accept error: %s",strerror(errno));
		}
		hrobot_tcp_receive(&ctrl_frame, data);
		close(clfd);
	}
}
