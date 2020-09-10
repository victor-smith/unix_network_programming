/*
 * tcpserv01.c
 *
 *  Created on: 2020年9月10日
 *      Author: jerray
 */
#include "cpph.h"


void str_echo(int socketfd)
{
	ssize_t n;
	char buf[MAXLINE];

again:
	while((n = read(socketfd, buf, MAXLINE)) > 0)
	{
		write(socketfd, buf, n);
	}

	if(n < 0 && errno == EINTR)
		goto again;
	else if(n<0)
	{
		printf("str_echo:read error\n");
		exit(-1);
	}
}

int main(int argc, char** argv)
{
	int listenfd, connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERVER_PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(0 != bind(listenfd, &servaddr, sizeof(servaddr)))
	{
		printf("bind error\n");
		exit(-1);
	}

	if(0 != listen(listenfd, 1024))
	{
		printf("listen failed\n");
		exit(-1);
	}

	for(;;)
	{
		clilen = sizeof(cliaddr);
		connfd = accept(listenfd, &cliaddr, &clilen);
		if(-1 == connfd)
		{
			printf("accept error \n");
			exit(-1);
		}
		else
		{
			if((childpid = fork()) == 0)
			{
				close(listenfd);
				str_echo(connfd);
				exit(0);
			}
		}
		close(connfd);
	}
	return 0;
}



