#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stddef.h>        /* for offsetof */
#include <string.h>        /* for convenience */
#include <unistd.h>        /* for convenience */
#include <errno.h>
#include <sys/socket.h>
#include <sys/time.h>

#include<netinet/in.h>//struct sockaddr_in
#include <pthread.h> //pthread support
 
#define BUFLEN	128
#define LISTENQ 20 

#define START_SEND_SPEED  0x20
#define STOP_SEND_SPEED   0x21

#define SA struct sockaddr

//#include "ctrlcmds.h"
//#include "ctrlprefix.h"
//#include "zynq_server.h"

int		connfd;
pthread_t tid;

void *send_speed(void *arg)
{
	int initSpeed = 0;
	unsigned char buff[4];
	int ret;
	while(*(int *)arg)
	{
		if(initSpeed == 999999)
		{
			initSpeed = 0;
		}
		sprintf(buff, "%d", initSpeed);
		ret = send(connfd, buff, 4, 0);
		if(ret < 0)
		{
			err_sys("send socket data error");
		}
		sleep(1);
		initSpeed++;
	}
	close(connfd);
	pthread_exit(NULL);
}
int zrobot_tcp_process()
{
	int n, err;
	int send_speed_flag = 1;
	unsigned char buff[5];
	//memset(&frame, 0, sizeof(TCP_CTRL_FRAME));
	int cmd = 0;
	int speed;
	printf("%d\n", cmd);
	while(1){
		memset(buff, 0, sizeof(buff));
		n = recv(connfd, buff, sizeof(buff), 0);
		if (n <= 0)
		{
			break;
		}
		sscanf(buff, "%d", &cmd);
		cmd = ntohs(cmd);
		printf("%d", cmd);
		switch(cmd)
		{
		case START_SEND_SPEED:
			send_speed_flag = 1;
			if((err = pthread_create(&tid, NULL, send_speed,
				&send_speed_flag)) != 0)
				perror("ZYNQ");
			break;
		case STOP_SEND_SPEED:
			send_speed_flag = 0;
			break;
		default:
			break;
		}
	}
	return 0;
}

void Listen(int fd, int backlog)
{
	char *ptr;

	if((ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);

	if(listen(fd, backlog) < 0)
		err_sys("listen error");
}
int main(int argc, char *argv[])
{
	int listenfd;
	struct sockaddr_in  servaddr, cliaddr;
	socklen_t len;
	char       buff[1024];
	
	if (argc != 1)
		err_quit("usage: ./%s",argv[0]);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == -1)
	{
		err_sys("socket failed");
	}
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(12345);

	bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
	Listen(listenfd, LISTENQ);

	for(; ;)
	{
		printf("accept\n");
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (SA *) &cliaddr, &len);
		if(connfd == -1)
		{
			err_sys("accept error");
		}
		printf("connection from %s, port %d\n",
				inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),
				ntohs(cliaddr.sin_port));
		zrobot_tcp_process();
		close(connfd);
	}
	exit(1);
}
